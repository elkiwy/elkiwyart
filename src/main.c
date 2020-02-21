#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


char* formattedString(char* format, char* s1);
char* stringRepl(char* s, char old, char new);

#include "utils.c"

#define PAGE_ITEM_BUFFER 32
#define PAGE_LINK_BUFFER 32
#define PAGE_CHILD_BUFFER 32
#define STR_BUF_LEN 64
#define MAX_PARAGRAPHS 32

char* html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='author' content='Stefano Bertoli'><link rel='stylesheet' type='text/css' href='../links/main.css'><title>ElKiwyArt</title></head><body>";
char* html_header = "<h1><a id='logo' href='home.html'>ElKiwyArt</a></h1>";
char *html_footer = "<p>Stefano Bertoli © 2020</p><button onclick=\" if(document.documentElement.getAttribute('data-theme')=='dark'){document.documentElement.setAttribute('data-theme', 'light');}else{document.documentElement.setAttribute('data-theme', 'dark');} \" type=\"button\">Theme</button></body></html>";



//////////////////////////////////////////////////////////////////////
// Structs
//////////////////////////////////////////////////////////////////////

//Content struct
typedef struct Content{
	char* data;
} Content;

//Page struct
typedef struct Page{
	//Page data
	char* name;
	char* filename;

	//Childs
	int children_len;
	struct Page* children[PAGE_CHILD_BUFFER];
	struct Page* parent;

	//Preview
	char* preview_description;
	bool has_preview;

	//Contents
	int contents_count;
	Content* contents[MAX_PARAGRAPHS];
} Page;



//////////////////////////////////////////////////////////////////////
//Page building
//////////////////////////////////////////////////////////////////////

///Build single navigation level
void build_nav_level(FILE* f, Page* p, char** path){
	fputs("<ul>", f);
	for (int i=0; i < p->children_len; ++i){
		//Search if you find this page in the path
		char* name = p->children[i]->name;
		char* filename = p->children[i]->filename;
		bool inPath = false;
		for (int j=0; j < 4; ++j){
			if (name == path[j]){inPath = true;}
		}

		//Add the item
		if (inPath){fprintf(f, "<li><a href='%s.html'><span>%s</span></a></li>", filename, name);  
		}else{fprintf(f, "<li><a href='%s.html'>%s</a></li>", filename, name);}
	}
	fputs("</ul>", f);
}

///Build whole navigation section
void build_nav(FILE* f, Page* p){
	fputs("<nav>", f);
	//Saves the page path
	char* path[4];
	path[0] = p->name;
	if (p->parent != NULL){
		path[1] = p->parent->name;
		if (p->parent->parent != NULL){
			path[2] = p->parent->parent->name;
			if (p->parent->parent->parent != NULL){
				path[3] = p->parent->parent->parent->name;
				build_nav_level(f, p->parent->parent->parent, path);
			}
			build_nav_level(f, p->parent->parent, path);
		}
		build_nav_level(f, p->parent, path);
	}
	build_nav_level(f, p, path);
	fputs("</nav>", f);
}

///Build single content
void build_content(FILE* f, Content* c){
	if (c==NULL) return;
	fputs(c->data, f);
}

///Build all the contents of a page
void build_contents(FILE* f, Page* p){
	fputs("<main>", f);

	//Page header
	if (p->parent !=NULL) {
		fprintf(f,"<h1 style=\"margin-bottom:0px\">%s</h1>", p->name);  
		fprintf(f,"<a href='%s.html'>Back to %s</a>", p->parent->filename, p->parent->name);
	}else{
		fprintf(f,"<h1>%s</h1>", p->name);  
	}

	//Page content
	for (int i=0; i<p->contents_count; ++i){
		build_content(f, p->contents[i]);
	}
	fputs("</main>", f);
}

///Build all the child previews for a parent page
void build_child_previews(FILE* f, Page* p){
	for (int i=0; i<p->children_len; ++i){
		if (p->children[i]->has_preview){
			//Page title
			fprintf(f, "<a href='%s.html'>", p->children[i]->filename);
			fprintf(f, "<h2 style=\"margin-bottom:0\">%s</h2>", p->children[i]->name);  
			fprintf(f, "</a>");

			//Page description
			fprintf(f, "<p>%s</p>", p->children[i]->preview_description);
		}
	}
}

///Build a whole page
void build_page(Page* page){
	//Get the proper filename
	char filename[STR_BUF_LEN];
	to_lowercase(page->filename, filename, STR_BUF_LEN);
	char filepath[STR_BUF_LEN];
	int result = snprintf(filepath, sizeof filepath, "../site/%s.html", filename);
	bool is_valid = result > 0 && (size_t)result < sizeof filename;
	if (!is_valid) {printf("Invalid filename: %s\n", filename); return;}
	snprintf(filepath, STR_BUF_LEN, "../site/%s.html", filename);

	//Create the file
	FILE* f = fopen(filepath, "w");

	//Header
	fprintf(f, html_head, page->name);
	fputs(html_header, f);

	//Navigation
	build_nav(f, page);

	//Page contents
	build_contents(f, page);

	//Child previews
	build_child_previews(f, page);
	
	//Footer
	fprintf(f, "<footer>%s</footer>", html_footer);

	//Close file
	fclose(f);
}

///Build this page and all his childs
void build_page_recursively(Page* page){
	if (page==NULL) return;
	printf("Building page %s and his %d childs.\n", page->name, page->children_len); fflush(stdout);
	build_page(page);

	for (int i=0; i<page->children_len; i++){
		build_page_recursively(page->children[i]);
	}
}



//////////////////////////////////////////////////////////////////////
//Page Creation
//////////////////////////////////////////////////////////////////////

///Create a new page
Page* create_page(Page* parent, char* name){
	printf("creating %s\n", name); fflush(stdout);
	Page* p = malloc( sizeof(Page) );
	p->name = name;
	p->filename = stringRepl(name, ' ', '_');
	p->parent = parent;
	p->children_len = 0;
	p->contents_count = 0;
	p->preview_description = "";
	p->has_preview = false;

	if (parent!=NULL){
		//Assign this page as a child for his parent
		parent->children[parent->children_len] = p;
		parent->children_len++;
	}
	return p;
}



//////////////////////////////////////////////////////////////////////
// Content Creation
//////////////////////////////////////////////////////////////////////

///Add a new paragraph to a page
void add_paragraph(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	cont->data = formattedString("<p>%s</p>", s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a new stub to a page
void add_stub(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	printf("!!! ADDING STUB\n"); fflush(stdout);
	cont->data = formattedString("<p style=\"color:red\">TODO: %s</p>", s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a new image to a page
void add_image(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	cont->data = formattedString("<img src='../media/img/%s'/>", s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add two new images side by side to a page
void add_image2(Page* p, char* s1, char* s2){
	Content* cont = malloc(sizeof(Content));
	char* format = "<div><img class='img2' src='../media/img/%s'/><img class='img2' src='../media/img/%s'/></div>";
	int size = strlen(s1)+strlen(s2)+strlen(format) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, s1, s2);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add three new images side by side to a page
void add_image3(Page* p, char* s1, char* s2, char* s3){
	Content* cont = malloc(sizeof(Content));
	char* format = "<div><img class='img3' src='../media/img/%s'/><img class='img3' src='../media/img/%s'/><img class='img3' src='../media/img/%s'/></div>";
	int size = strlen(s1)+strlen(s2)+strlen(s3)+strlen(format) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, s1, s2, s3);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a new header to a page
void add_header(Page* p, char* s, int hSize){
	Content* cont = malloc(sizeof(Content));
	char* buff = malloc(sizeof(char)*strlen(s)+9+1);
	sprintf(buff, "<h%d>%s</h%d>", hSize, s, hSize);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a preview description to a page
void add_preview_description(Page* p, char* s){
	p->has_preview = true;
	p->preview_description = s;
}



//////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////

int main(){
    #include "content.c"
	printf("-----\nStart building\n-----\n"); fflush(stdout);
	build_page_recursively(home);
	return 0;
}

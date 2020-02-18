#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "utils.c"

#define PAGE_ITEM_BUFFER 32
#define PAGE_LINK_BUFFER 32
#define PAGE_CHILD_BUFFER 32
#define STR_BUF_LEN 64
#define MAX_PARAGRAPHS 32


char* html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='author' content='Stefano Bertoli'><link rel='stylesheet' type='text/css' href='../links/main.css'><title>ElKiwyArt</title></head><body>";
char* html_header = "<h1><a id='logo' href='home.html'>ElKiwyArt</a></h1>";
char *html_footer = "FOOTER<button onclick=\" if(document.documentElement.getAttribute('data-theme')=='dark'){document.documentElement.setAttribute('data-theme', 'light');}else{document.documentElement.setAttribute('data-theme', 'dark');} \" type=\"button\">Theme</button></body></html>";


typedef struct Paragraph{
	char* content;
} Paragraph;

typedef struct Page{
	char* name;
	char* items_tags[PAGE_ITEM_BUFFER];
	char* items_text[PAGE_ITEM_BUFFER];
	char* items_meta[PAGE_ITEM_BUFFER];

	char* link_names[PAGE_LINK_BUFFER];
	char* link_urls[PAGE_LINK_BUFFER];

	int children_len;
	struct Page* children[PAGE_CHILD_BUFFER];
	struct Page* parent;

	char* preview_description;
	bool has_preview;

	int paragraph_count;
	Paragraph* paragraphs[MAX_PARAGRAPHS];

} Page;







void build_nav_level(FILE* f, Page* p, char** path){
	fputs("<ul>", f);
	for (int i=0; i < p->children_len; ++i){
		//Search if you find this page in the path
		char* name = p->children[i]->name;
		bool inPath = false;
		for (int j=0; j < 4; ++j){
			if (name == path[j]){inPath = true;}
		}

		//Add the item
		if (inPath){fprintf(f, "<li><span>%s</span></li>", name);  
		}else{fprintf(f, "<li><a href='%s.html'>%s</a></li>", name, name);}
	}
	fputs("</ul>", f);
}



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



void build_paragraph(FILE* f, Paragraph* p){
	if (p==NULL) return;
	fprintf(f,"<p>%s</p>", p->content);  
}


void build_content(FILE* f, Page* p){
	fputs("<main>", f);
	fprintf(f,"<h1>%s</h1>", p->name);  
	for (int i=0; i<p->paragraph_count; ++i){
		build_paragraph(f, p->paragraphs[i]);
	}
	fputs("</main>", f);
}

void build_child_previews(FILE* f, Page* p){
	for (int i=0; i<p->children_len; ++i){
		if (p->children[i]->has_preview){
			fprintf(f,"<h2 style=\"margin-bottom:0\">%s</h2>", p->children[i]->name);  
			fputs("<p>", f);
			fputs(p->children[i]->preview_description, f);
			fputs("</p>", f);
		}
	}
}

void build_page(Page* page){
	char filename[STR_BUF_LEN];
	to_lowercase(page->name, filename, STR_BUF_LEN);
	char filepath[STR_BUF_LEN];
	int result = snprintf(filepath, sizeof filepath, "../site/%s.html", filename);
	bool is_valid = result > 0 && (size_t)result < sizeof filename;
	if (!is_valid) {
		printf("Invalid filename: %s\n", filename);
		return;
	}

	snprintf(filepath, STR_BUF_LEN, "../site/%s.html", filename);
	FILE* f = fopen(filepath, "w");

	fprintf(f, html_head, page->name);
	fputs(html_header, f);
	build_nav(f, page);

	build_content(f, page);

	build_child_previews(f, page);

	fputs(html_footer, f);
	fclose(f);
}



Page* create_page(Page* parent, char* name){
	Page* p = malloc( sizeof(Page) );
	p->name = name;
	p->parent = parent;
	p->children_len = 0;
	p->paragraph_count = 0;
	p->preview_description = "";
	p->has_preview = false;

	printf("creating %s\n", name); fflush(stdout);
	if (parent!=NULL){
		//Assign this page as a child for his parent
		printf("Children count %d for %s.\n", parent->children_len, parent->name); fflush(stdout);
		parent->children[parent->children_len] = p;
		parent->children_len++;
	}

	return p;
}


void build_page_recursively(Page* page){
	if (page==NULL) return;
	printf("Building page and his %d childs.\n", page->children_len); fflush(stdout);
	build_page(page);

	for (int i=0; i<page->children_len; i++){
		build_page_recursively(page->children[i]);
	}
}




void add_paragraph(Page* p, char* s){
	Paragraph* par = malloc(sizeof(Paragraph));
	par->content = s;
	p->paragraphs[p->paragraph_count] = par;
	p->paragraph_count++;
}

void add_preview_description(Page* p, char* s){
	p->has_preview = true;
	p->preview_description = s;
}



int main(){

    #include "content.c"


	printf("-----\nStart building\n-----\n"); fflush(stdout);

	build_page_recursively(home);

	return 0;
}

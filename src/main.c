#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


char* joinStrings(int n, ...);
char* joinStringsArr(int n, char** arr);
char* formatString(char* format, int n, ...);
char* stringRepl(char* s, char old, char new);
char* clickableImg(char* src, char* class);

#include "utils.c"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define PAGE_ITEM_BUFFER 32
#define PAGE_LINK_BUFFER 32
#define PAGE_CHILD_BUFFER 32
#define STR_BUF_LEN 64
#define MAX_CONTENTS 32

#define STAT_NODATA 0
#define STAT_PAUSED 1
#define STAT_ONGOING 2
#define STAT_FINISHED 3
#define STAT_SUSPENDED 4
#define STAT_TOSTART 5

char* html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='author' content='Stefano Bertoli'><link rel='stylesheet' type='text/css' href='../links/main.css'><title>ElKiwyArt</title></head><body>";
char* html_header = "<h1><a id='logo' href='home.html'>ElKiwyArt</a></h1>";
char *html_footer = "<p>Stefano Bertoli © 2020</p></body></html>";



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
	char* preview_image;
	bool has_preview;

	//Project status
	int status;

	//Contents
	int contents_count;
	Content* contents[MAX_CONTENTS];

	//References
	int references_count;
	Content* references[MAX_CONTENTS];
} Page;






void resize_image(const char* filename, float width_percent, float height_percent, const char* output){
	int w, h, n;
	unsigned char* input_data = stbi_load(filename, &w, &h, &n, 0);
	if (!input_data){
		printf("Image %s could not be loaded.\n", filename);fflush(stdout);
		return;
	}

	int out_w = (int)(w * width_percent);
	int out_h = (int)(h * height_percent);
	unsigned char* output_data = (unsigned char*)malloc(out_w * out_h * n);

	stbir_resize(input_data, w, h, 0, output_data, out_w, out_h, 0, STBIR_TYPE_UINT8, n, STBIR_ALPHA_CHANNEL_NONE, 0, STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP, STBIR_FILTER_BOX, STBIR_FILTER_BOX, STBIR_COLORSPACE_LINEAR, NULL);
	stbi_image_free(input_data);
	stbi_write_png(output, out_w, out_h, n, output_data, 0);
	free(output_data);
}






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
	//Page header
	if (p->parent !=NULL) {
		fprintf(f,"<a href='%s.html'>", p->parent->filename);
		fprintf(f,"<h3 class='link' style='display:inline'>%s</h3>", p->parent->name);  
		fprintf(f,"</a>");
		fprintf(f,"<h3 style='display:inline'> :: </h3>");  
		fprintf(f,"<h1 style='display:inline-block;margin-bottom:0px'>%s</h1></br>", p->name);  
	}else{
		fprintf(f,"<h1>%s</h1>", p->name);  
	}

	if(p->status != STAT_NODATA){
		char* s;
		switch(p->status){
		case STAT_PAUSED:    s = "<span style='color:#aa5a00;font-weight:bold'>Paused</span>";break;
		case STAT_ONGOING:   s = "<span style='color:#06898c;font-weight:bold'>On going</span>";break;
		case STAT_SUSPENDED: s = "<span style='color:#920700;font-weight:bold'>Suspended</span>";break;
		case STAT_FINISHED:  s = "<span style='color:#038f15;font-weight:bold'>Completed</span>";break;
		case STAT_TOSTART:   s = "<span style='color:#77860c;font-weight:bold'>About to start</span>";break;
		}
			
		fprintf(f, "<span style='display:inline-block;margin-bottom:24px;font-size:14px'>[The development is: %s]</span>", s);
	}else{
		fputs("<div style='height:24px'></div>", f);
	}


	//Page content
	for (int i=0; i<p->contents_count; ++i){
		build_content(f, p->contents[i]);
	}
}

///Build all the child previews for a parent page
void build_child_previews(FILE* f, Page* p){
	if(p->children_len>0){
		fputs("<div style='height:24px'></div>", f);
		for (int i=0; i<p->children_len; ++i){
			if (p->children[i]->has_preview){
				fputs("<div class='preview'>", f);

				fprintf(f, "<a href='%s.html'>", p->children[i]->filename);
				if (p->children[i]->preview_image != NULL){
					fprintf(f, "<div class='imgprevcont'><img class='imgprev' src='../media/img/%s'></div>", p->children[i]->preview_image);
				}

				//Page title
				fputs("<div class='textprevcont'>", f);
				fprintf(f, "<h2 class='titleprev' style=\"margin-bottom:0\"><a class='link' href='%s.html'>%s</a></h2>", p->children[i]->filename, p->children[i]->name);  
				fprintf(f, "</a>");

				//Page description
				fprintf(f, "<p class='descprev'>%s</p>", p->children[i]->preview_description);
				fputs("</div>", f);
				fputs("</div>", f);
			}
		}
	}
}

void build_references(FILE* f, Page* p){
	if(p->references_count>0 ){
		fputs("<div>", f);
		fputs("<h2 style='margin-top:32px'>References:</h2>", f);
		for(int i=0; i<p->references_count; ++i){
			fprintf(f, "%s", p->references[i]->data);
		}
		fputs("</div>", f);
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
	fputs("<main>", f);
	build_contents(f, page);

	//Child previews
	build_child_previews(f, page);

	//References
	build_references(f, page);
	fputs("</main>", f);
	
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
	p->references_count = 0;
	p->preview_description = "";
	p->preview_image = NULL;
	p->has_preview = false;
	p->status = STAT_NODATA;

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

void set_status(Page* p, int s){
	p->status = s;
}

///Add a new paragraph to a page
void add_paragraph(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	cont->data = formatString("<p>%s</p>", 1, s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a new stub to a page
void add_stub(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	printf("!!! ADDING STUB\n"); fflush(stdout);
	cont->data = formatString("<p style=\"color:red\">TODO: %s</p>", 1, s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a new reference to a page
void add_reference(Page* p, char* text, char* link){
	Content* cont = malloc(sizeof(Content));
	char* format = "<div style='margin-bottom:2px'> %s <span style='position:absolute;left:320px'> =&gt; </span> <span style='float:right;max-width:320px;white-space:nowrap;overflow:hidden;text-overflow:ellipsis'><a class='link' href='%s'>%s</a></span> </div>";
	char* buff = malloc(sizeof(char)*(strlen(text)+strlen(format)+(strlen(link)*2)+1));
	sprintf(buff, format, text, link, link);
	cont->data = buff;
	p->references[p->references_count] = cont;
	p->references_count++;
}


void prepare_thumbnail(const char* filename){
	char* input_format = "../media/img/%s";
	char* input_path = malloc(sizeof(char)*(strlen(input_format)+strlen(filename)+1));
	sprintf(input_path, input_format, filename);

	char* output_format = "../media/thumb/%s";
	char* output_path = malloc(sizeof(char)*(strlen(output_format)+strlen(filename)+1));
	sprintf(output_path, output_format, filename);

	resize_image(input_path, 0.5, 0.5, output_path);
}

///Add a new image to a page
void add_image(Page* p, char* s){
	prepare_thumbnail(s);
	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s, "img1");
	cont->data = img1;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add two new images side by side to a page
void add_image2(Page* p, char* s1, char* s2){
	prepare_thumbnail(s1);
	prepare_thumbnail(s2);
	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s1, "img2");
	char* img2 = clickableImg(s2, "img2");
	char* format = "<div class='img2cont'>%s%s</div>";
	int size = strlen(img1) + strlen(img2) + strlen(format) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, img1, img2);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add three new images side by side to a page
void add_image3(Page* p, char* s1, char* s2, char* s3){
	prepare_thumbnail(s1);
	prepare_thumbnail(s2);
	prepare_thumbnail(s3);
	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s1, "img3");
	char* img2 = clickableImg(s2, "img3");
	char* img3 = clickableImg(s3, "img3");
	char* format = "<div class='img3cont'>%s%s%s</div>";
	int size = strlen(img1) + strlen(img2) + strlen(img3) + strlen(format) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, img1, img2, img3);
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

///Add a new number list to a page
void add_list(Page* p, bool numbered, int n, ...){
	va_list args;
	char* listItems[n];

	//Build all the list items
	va_start(args, n);
	for (int i=0; i<n; ++i){
		listItems[i] = formatString("<li>%s</li>", 1, va_arg(args, char*));
	}
	va_end(args);

	//Pack them into a string and add <ul> tag
	char* joinedListItems = joinStringsArr(n, listItems);
	char* format = "<ul>%s</ul>";
	if (numbered) format = "<ol>%s</ol>";

	char* data = formatString(format, 1, joinedListItems);

	//Create the content
	Content* cont = malloc(sizeof(Content));
	cont->data = data;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///Add a preview description to a page
void add_preview_description(Page* p, char* s){
	p->has_preview = true;
	p->preview_description = s;
}

///Add a preview image to a page
void add_preview_image(Page* p, char* s){
	p->preview_image = s;	
}


char* dropLast(char* src, int n){
	int size = strlen(src)-n;
	char* buff = malloc(sizeof(char)*(size + 1));
	for (int i=0; i<size; ++i){
		buff[i] = src[i];
	}
	buff[size] = '\0';
	return buff;
}

void add_gallery(Page* p, int n, ...){
	va_list ap;
	char* strings[n];
	va_start(ap, n);
	for(int i=0; i<n; ++i){
		//strings[i] = clickableImg(va_arg(ap, char*), "galleryImage");
		char* s = va_arg(ap, char*);
		strings[i] = formatString("<div class='galleryImage'><a href='../media/img/%s'><img src='../media/img/%s'><span class='galleryDesc'>%s</span></a></div>", 3, s, s, dropLast(s, 4));
	}
	va_end(ap);

	//Pack them into a string and add <ul> tag
	char* joinedImages = joinStringsArr(n, strings);
	char* data = formatString("<div class='gallery'>%s</div>", 1, joinedImages);

	//Create the content
	Content* cont = malloc(sizeof(Content));
	cont->data = data;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}


//////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////

int main(){
    #include "content.c"

	//Make site dire if not already there
	struct stat st = {0};
	if (stat("../site", &st) == -1) mkdir("../site", 0700);
	if (stat("../media/thumb", &st) == -1) mkdir("../media/thumb", 0700);
	

	printf("-----\nStart building\n-----\n"); fflush(stdout);
	build_page_recursively(p0);
	return 0;
}

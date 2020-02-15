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


char* html_head = "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='author' content='Stefano Bertoli'><link rel='stylesheet' type='text/css' href='../links/main.css'><title>ElKiwyArt</title></head><body>";
char* html_header = "<header><a id='logo' href='home.html'>ElKiwyArt</a></header>";
char *html_footer = "FOOTER</body></html>";



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
} Page;




void build_nav_level(FILE* f, Page* p){
	fputs("<ul>", f);
	for (int i=0; i < p->children_len; ++i){
		char* name = p->children[i]->name;
        fprintf(f, "<li><a href='%s.html'>%s</a></li>", name, name);  
	}
	fputs("</ul>", f);
}



void build_nav(FILE* f, Page* p){
	fputs("<nav>", f);
	if (p->parent != NULL){
		if (p->parent->parent != NULL){
			if (p->parent->parent->parent != NULL){
				build_nav_level(f, p->parent->parent->parent);
			}
			build_nav_level(f, p->parent->parent);
		}
		build_nav_level(f, p->parent);
	}
	build_nav_level(f, p);
	fputs("</nav>", f);
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
	fputs("<main>", f);
	build_nav(f, page);

	fprintf(f,"<h1>%s</h1>", page->name);  
	fputs("</main>", f);
	fputs(html_footer, f);
	fclose(f);
}



Page* create_page(Page* parent, char* name){
	Page* p = malloc( sizeof(Page) );
	p->name = name;
	p->parent = parent;
	p->children_len = 0;

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


int main(){
	Page* home = create_page(NULL, "home");
	create_page(home, "blog");
	create_page(home, "art");
	create_page(home, "programs");
	create_page(home, "games");
	create_page(home, "about");


	printf("-----\nStart building\n-----\n"); fflush(stdout);

	build_page_recursively(home);

	return 0;
}

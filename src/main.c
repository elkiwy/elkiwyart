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
	fputs("test", f);
	fputs("</main>", f);
	fputs(html_footer, f);
	fclose(f);
}


Page create_page(Page* parent, char* name){
	Page p;
	p.name = name;
	p.parent = parent;
	return p;
}



int main(){

	Page home     = create_page(NULL, "home");
	Page blog     = create_page(&home, "blog");
	Page art      = create_page(&home, "art");
	Page programs = create_page(&home, "programs");
	Page games    = create_page(&home, "games");
	Page about    = create_page(&home, "about");

	Page* pages[] = { &home, &blog, &art, &programs, &games, &about};

	int pages_count = sizeof pages / sizeof pages[0];

	for (int i=0; i<pages_count; ++i){
		Page* p = pages[i];
		if (p->parent){
			p->parent->children[p->parent->children_len] = p;
			p->parent->children_len++;
		}
	}

	for (int i=0; i<pages_count; ++i){
		build_page(pages[i]);
	}

	return 0;
}

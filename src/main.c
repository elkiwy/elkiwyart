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
char* clickableImg(char* src, char* class, char* style);

//#define CREATING_THUMBNAILS

#include "utils.c"


#ifdef CREATING_THUMBNAILS
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_STATIC
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#define PAGE_ITEM_BUFFER 32
#define PAGE_LINK_BUFFER 32
#define PAGE_CHILD_BUFFER 32
#define STR_BUF_LEN 64
#define MAX_CONTENTS 128

#define STAT_NODATA 0
#define STAT_PAUSED 1
#define STAT_ONGOING 2
#define STAT_FINISHED 3
#define STAT_SUSPENDED 4
#define STAT_TOSTART 5


char* html_head = "<meta charset='utf-8'><meta name='author' content='Stefano Bertoli'><link rel='stylesheet' type='text/css' href='../links/main.css'>";
char* html_header = "<h1><a id='logo' href='home.html'>ElKiwyArt</a></h1>";
char *html_footer = "<p>Stefano Bertoli © 2020</p>";



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






#ifdef CREATING_THUMBNAILS
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
void image_size(const char* filename, int* w, int* h, int* n){
	unsigned char* input_data = stbi_load(filename, w, h, n, 0);
	if (!input_data){
		printf("Image %s could not be loaded.\n", filename);fflush(stdout);
		*w = 0;
		*h = 0;
		*n = 0;
		return;
	}
	free(input_data);
}
#endif


void prepare_thumbnail(const char* filename){
	#ifdef CREATING_THUMBNAILS
		char* input_format = "../media/img/%s";
		char* input_path = malloc(sizeof(char)*(strlen(input_format)+strlen(filename)+1));
		sprintf(input_path, input_format, filename);

		char* output_format = "../media/thumb/%s";
		char* output_path = malloc(sizeof(char)*(strlen(output_format)+strlen(filename)+1));
		sprintf(output_path, output_format, filename);

		resize_image(input_path, 0.5, 0.5, output_path);
	#else
		printf("Skipping thumb %s\n", filename);
	#endif
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



//////////////////////////////////////////////////////////////////////
///=Pages building
//////////////////////////////////////////////////////////////////////

void build_head_tags(FILE* f, Page* p){

	fputs("<!-- Normal meta tags -->", f);
	fprintf(f, "<meta charset='utf-8'>");
	fprintf(f, "<meta name='viewport' content='width=device-width'>");
	fprintf(f, "<meta name='description' content='%s'>", p->preview_description);
	fprintf(f, "<meta name='keywords' content='elkiwyart, elkiwy, elkiwy art, generative, processing, coding, programming'>");
	fprintf(f, "<meta name='author' content='Stefano Bertoli'>");
	fprintf(f, "<link rel='canonical' href='https://elkiwyart.com/site/%s.html'>", p->filename);
	fprintf(f, "<title>ElKiwyArt | %s</title>", p->name);

	fprintf(f, "<!-- twitter cards -->");
	fprintf(f, "<meta name='twitter:card' content='summary' />");
	fprintf(f, "<meta name='twitter:site' content='@elkiwydev' />");
	fprintf(f, "<meta name='twitter:creator' content='@elkiwydev' />");

	fprintf(f, "<!-- Open Graph stuff -->");
	fprintf(f, "<meta property='og:title' content='ElKiwyArt | %s'>", p->name);
	fprintf(f, "<meta property='og:type' content='article'>");
	fprintf(f, "<meta property='og:description' content='%s'>", p->preview_description);

#ifdef CREATING_THUMBNAILS
	if(p->has_preview && p->preview_image!=NULL){
		int w = 0;
		int h = 0;
		int n = 0;
		char* img_format = "../media/thumb/%s";
		char* img_path = malloc(sizeof(char)*(strlen(img_format)+strlen(p->preview_image)+1));
		sprintf(img_path, img_format, p->preview_image);
		image_size(img_path, &w, &h, &n);
		fprintf(f, "<meta property='og:image' content='https://elkiwyart.com/media/img/%s'>", p->preview_image);
		fprintf(f, "<meta property='og:image:width' content='%d'>", w);
		fprintf(f, "<meta property='og:image:height' content='%d'>", h);
	}
#endif
	fprintf(f, "<meta property='og:url' content='https://elkiwyart.com/site/%s.html'>", p->filename);

	fprintf(f, "<!-- Robots -->");
	fprintf(f, "<meta name='robots' content='index, aboutme'>");
}




///~Build a single navigation level, helper for build_nav
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
		char lowercaseFilename[STR_BUF_LEN];
		to_lowercase(filename, lowercaseFilename, STR_BUF_LEN);
		if (inPath){fprintf(f, "<li><a href='%s.html'><span>%s</span></a></li>", lowercaseFilename, name);  
		}else{fprintf(f, "<li><a href='%s.html'>%s</a></li>", lowercaseFilename, name);}
	}
	fputs("</ul>", f);
}

///~Build all the navigation levels
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

///~Build a single raw content, helper for build_contents
void build_content(FILE* f, Content* c){
	if (c==NULL) return;
	fputs(c->data, f);
}

///~Build all the page contents
void build_contents(FILE* f, Page* p){
	//Page header
	if (p->parent !=NULL) {
		char lowercaseFilename[STR_BUF_LEN];
		to_lowercase(p->parent->filename, lowercaseFilename, STR_BUF_LEN);
		fprintf(f,"<a href='%s.html'>", lowercaseFilename);
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
		//fputs("<div style='height:4px'></div>", f);
	}

	//Page content
	for (int i=0; i<p->contents_count; ++i){
		build_content(f, p->contents[i]);
	}
}

///~Build all the previews of the page's childs
void build_child_previews(FILE* f, Page* p){
	if(p->children_len>0){
		fputs("<div style='height:24px'></div>", f);
		for (int i=0; i<p->children_len; ++i){
			if (p->children[i]->has_preview){
				fputs("<div class='preview'>", f);

				char lowercaseFilename[STR_BUF_LEN];
				to_lowercase(p->children[i]->filename, lowercaseFilename, STR_BUF_LEN);
				fprintf(f, "<a href='%s.html'>", lowercaseFilename);
				if (p->children[i]->preview_image != NULL){
#ifdef CREATING_THUMBNAILS
					fprintf(f, "<div class='imgprevcont'><img class='imgprev' src='../media/thumb/%s'></div>", p->children[i]->preview_image);
#else
					fprintf(f, "<div class='imgprevcont'><img class='imgprev' src='../media/img/%s'></div>", p->children[i]->preview_image);
#endif
				}

				//Page title
				fputs("<div class='textprevcont'>", f);
				fprintf(f, "<h2 class='titleprev' style=\"margin-bottom:0\"><a class='link' href='%s.html'>%s</a></h2>", lowercaseFilename, p->children[i]->name);  
				fprintf(f, "</a>");

				//Page description
				fprintf(f, "<p class='descprev'>%s</p>", p->children[i]->preview_description);
				fputs("</div>", f);
				fputs("</div>", f);
			}
		}
	}
}

///~Build all the page references
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

///~Fully build a page
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

	fputs("<!DOCTYPE html><html lang='en'>", f);
	fputs("<head>", f);
	fprintf(f, html_head, page->name);
	build_head_tags(f, page);
	fputs("</head>", f);
	fputs("<body>", f);
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
	fputs("</body>", f);
	fputs("</html>", f);

	//Close file
	fclose(f);
}

///~Build this page and all his childs
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
///=Content Creation
//////////////////////////////////////////////////////////////////////

///~Sets the status of a page
void set_status(Page* p, int s){
	p->status = s;
}

///~Adds a new paragraph to a page
void add_paragraph(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	cont->data = formatString("<p>%s</p>", 1, s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}


///~Adds a raw html from another file
void add_html(Page* p, char* path){
	Content* cont = malloc(sizeof(Content));

	FILE* f = fopen(path, "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buff = malloc(sizeof(char) * (fsize + 1));
	fread(buff, sizeof(char), fsize, f);
	fclose(f);

	cont->data = formatString("<p>%s</p>", 1, buff);
	free(buff);


	p->contents[p->contents_count] = cont;
	p->contents_count++;
}



///~Add a new stub to a page, printing a warning during the execution.
void add_stub(Page* p, char* s){
	Content* cont = malloc(sizeof(Content));
	printf("!!! ADDING STUB\n"); fflush(stdout);
	cont->data = formatString("<p style=\"color:red\">TODO: %s</p>", 1, s);
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///~Add a new reference to a page bottom
void add_reference(Page* p, char* text, char* link){
	Content* cont = malloc(sizeof(Content));
	char* format = "<div style='margin-bottom:2px'> %s <span style='position:absolute;left:320px'> =&gt; </span> <span style='float:right;max-width:320px;white-space:nowrap;overflow:hidden;text-overflow:ellipsis'><a class='link' href='%s'>%s</a></span> </div>";
	char* buff = malloc(sizeof(char)*(strlen(text)+strlen(format)+(strlen(link)*2)+1));

	char lowercaseLink[STR_BUF_LEN];
	to_lowercase(link, lowercaseLink, STR_BUF_LEN);
	sprintf(buff, format, text, lowercaseLink, link);
	cont->data = buff;
	p->references[p->references_count] = cont;
	p->references_count++;
}

///~Add a single image to a page
void add_image(Page* p, char* s){
	prepare_thumbnail(s);
	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s, "img1", "");
	cont->data = img1;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///~Add a new image with a simple description text below it
void add_image_desc(Page* p, char* s, char* d){
	prepare_thumbnail(s);

	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s, "img1", "margin-bottom:0px");

	char* format = "<div>%s<span class='imgdesc'>%s</span></div>";
	char* buff = malloc(sizeof(char)*(strlen(format) + strlen(img1) + strlen(d) + 1));
	sprintf(buff, format, img1, d);
	free(img1);

	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;

}

///~Add two new images side by side
void add_image2(Page* p, char* s1, char* s2){
	prepare_thumbnail(s1);
	prepare_thumbnail(s2);
	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s1, "img2", "");
	char* img2 = clickableImg(s2, "img2", "");
	char* format = "<div class='img2cont'>%s%s</div>";
	int size = strlen(img1) + strlen(img2) + strlen(format) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, img1, img2);
	free(img1);
	free(img2);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///~Add three new images side by side
void add_image3(Page* p, char* s1, char* s2, char* s3){
	prepare_thumbnail(s1);
	prepare_thumbnail(s2);
	prepare_thumbnail(s3);
	Content* cont = malloc(sizeof(Content));
	char* img1 = clickableImg(s1, "img3", "");
	char* img2 = clickableImg(s2, "img3", "");
	char* img3 = clickableImg(s3, "img3", "");
	char* format = "<div class='img3cont'>%s%s%s</div>";
	int size = strlen(img1) + strlen(img2) + strlen(img3) + strlen(format) + 1;
	char* buff = malloc(sizeof(char)*size);
	sprintf(buff, format, img1, img2, img3);
	free(img1); free(img2); free(img3);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///~Add a new header with a specific size
void add_header(Page* p, char* s, int hSize){
	Content* cont = malloc(sizeof(Content));
	char* buff = malloc(sizeof(char)*strlen(s)+9+1);
	sprintf(buff, "<h%d>%s</h%d>", hSize, s, hSize);
	cont->data = buff;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///~Add a new list of n items. Can be numbered or simply dotted.
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
	for (int i=0; i<n; ++i){free(listItems[i]);}

	char* data = formatString(format, 1, joinedListItems);
	free(joinedListItems);

	//Create the content
	Content* cont = malloc(sizeof(Content));
	cont->data = data;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}

///~Add a description to the page's preview
void add_preview_description(Page* p, char* s){
	p->has_preview = true;
	p->preview_description = s;
}

///~Add a image to the page's preview (requires also a description to be displayed)
void add_preview_image(Page* p, char* s){
	prepare_thumbnail(s);
	p->preview_image = s;	
}

///~Add n images at the bottom of the page
void add_gallery(Page* p, int n, ...){
	va_list ap;
	char* strings[n];
	va_start(ap, n);
	for(int i=0; i<n; ++i){
		char* s = va_arg(ap, char*);
		char* s1 = dropLast(s, 4);
		char lowercaseFilename[STR_BUF_LEN];
		to_lowercase(s, lowercaseFilename, STR_BUF_LEN);
		strings[i] = formatString("<div class='galleryImage'><a href='../media/img/%s'><img src='../media/img/%s'><span class='galleryDesc'>%s</span></a></div>", 3, s, s, s1);
		free(s1);
	}
	va_end(ap);

	//Pack them into a string and add <ul> tag
	char* joinedImages = joinStringsArr(n, strings);
	char* data = formatString("<div class='gallery'>%s</div>", 1, joinedImages);
	free(joinedImages);
	for(int i=0; i<n; ++i){
		free(strings[i]);
	}


	//Create the content
	Content* cont = malloc(sizeof(Content));
	cont->data = data;
	p->contents[p->contents_count] = cont;
	p->contents_count++;
}


//////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////
void free_content(Content* c){
	free(c->data);
	free(c);
}
void free_page(Page* p){

	for (int i=0; i<p->references_count; i++){
		free_content(p->references[i]);
	}

	for (int i=0; i<p->contents_count; i++){
		free_content(p->contents[i]);
	}

	for (int i=0; i<p->children_len; i++){
		free_page(p->children[i]);
	}
	free(p->filename);
	free(p);
}

int main(){
    #include "content.c"

	//Make site dire if not already there
	struct stat st = {0};
	if (stat("../site", &st) == -1) mkdir("../site", 0700);
	if (stat("../media/thumb", &st) == -1) mkdir("../media/thumb", 0700);

	printf("-----\nStart building\n-----\n"); fflush(stdout);
	build_page_recursively(p0);
	free_page(p0);
	return 0;
}

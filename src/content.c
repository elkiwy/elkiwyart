
#define LINK(url)           "<a class='link' href='"url"' class='external' target='_blank'>"url"</a>"
#define LINKTEXT(url, name) "<a class='link' href='"url"' class='external' target='_blank'>"name"</a>"

#define SEND(page)           "<a class='link' href='" page ".html'>" page "</a>"
#define SENDTEXT(page, text) "<a class='link' href='" page ".html'>" text "</a>"

#define IMAGE(name) "<img src='../media/identity/" name "'/>"
#define PAR(content) "<p>" content "</p>"
#define MONOSPACE(content) "<span style='font-family:monospace'>" content "</span>"
#define BOLD(content) "<b>" content "</b>"


#define HEADER_SIZE_SMALL 2



////////////////////////////
// Home
////////////////////////////
Page* p0 = NULL;
{
	p0 = create_page(NULL, "Home");
	add_paragraph(p0, "Welcome to ElKiwyArt website!");
	add_paragraph(p0, "This is my very personal attempt to show who am I, and what I do. Since I do many different things sprinkled around the internet, the scope of this website is to try group all up and present everything to you in a nice and clear way.");
	add_paragraph(p0, "But, this is not a portfolio where i present everything I made or released. There will also be random posts on anything I do in a particular time in my life, maybe some big project, or maybe just a little dumb study on something." );
	add_image(p0, "default_1080.png");
	add_stub(p0, "Closing");


////////////////////////////
// Art
////////////////////////////
	{
		Page* p1 = create_page(p0, "Art");
		add_paragraph(p1, "This is a collection of my studies on generative art.");


		{
			Page* p2 = create_page(p1, "Gates");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "Third study on procedurally generated trees, going for a more abstract and twisted shapes.");
			add_preview_image(p2, "Gates_96650.png");
			add_paragraph(p2, "I really enjoyed the natural look of Scorci , but after that I started to want back some of the regular and geometric feel typical of generative art. So what's better than some natural-ish tree with weird geometric shapes? ");
			add_header(p2, "One more tree iteration", HEADER_SIZE_SMALL);
			add_paragraph(p2, "This may starts to feel a bit repetitive, but I wanted to get one more artwork with this style. The process to achieve these pieces has been pretty simple this time. I had to take the old tree function and tweak it to accept a path as input for the main trunk. Before these changes, that function was accepting just a single point and a starting direction for the tree to grow, but that had two major problems:");
			char* l1 = "The final structure of the tree was not predictable. Half of the times the tree would start in the right spot, then curving out of the canvas letting me with a bunch of nothing on the screen.";
			char* l2 = "I could not give the tree a fixed shape and then let the minor branches go where they wanted.";
			add_list(p2, false, 2, l1, l2);
			add_image(p2, "start0.png");
			add_paragraph(p2, "After some changes I had something that could work for what I wanted to do:");
			add_image2(p2, "straight0.png", "straight1.png");
			add_paragraph(p2, "Once that the tree was following whatever the path I wanted, I had to find some nice shapes to draw.");
			add_image2(p2, "rectangle0.png", "rectangle1.png");
			add_image2(p2, "rectangles0.png", "rectangles1.png");
			add_paragraph(p2, "The concept was there, but the idea of trees floating mid-air with no roots to keep them anchored somewhere wasn't really right for this kind of artwork, so I had to add something to give some stability to the drawing.");
			add_paragraph(p2, "(Sadly I can't show this part of the process because I lost the images from that day)");
			add_paragraph(p2, "After some minor tweaks the series was ready to start the full resolution generation.");
			add_gallery(p2, 6 ,"Gates_96650.png" ,"Gates_617167.png" ,"Gates_619683.png" ,"Gates_932704.png" ,"Gates_141067.png" ,"Gates_965820.png");
		}

		{
			Page* p2 = create_page(p1, "Scorci");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "Second study on procedurally generated trees synthesising a Japanese panorama.");
			add_preview_image(p2, "Scorci 137931.png");
			add_header(p2, "A rework of Spring Flowers", HEADER_SIZE_SMALL);
			add_paragraph(p2, "To everyone that saw my previous posts, these new pieces could feel pretty similar to the series \"Spring Flowers\" since I reused the tree and flower structure and expanded that concept into a more complete tribute to the Ukiyo-E style Japanese woodprints.");
			add_paragraph(p2, "The previous series was pretty minimalist and plain, but this new rework aimed to give the right mood to that concept by giving more context of the surrounding of that tree.");
			add_header(p2, "Giving some space", HEADER_SIZE_SMALL);
			add_paragraph(p2, "The first thing to do was adding a Bi-Linear gradient on top of everything that shades darker on the top and the bottom of the artwork, this gives a sense of space by giving a subtle hint of where the sky, ground, and horizon line is in the canvas.");
			add_paragraph(p2, "This small detail alone already gave the artwork a totally different mood and feel.");
			add_image2(p2, "gradient0.png", "gradient1.png");
			add_header(p2, "Lighten up the image", HEADER_SIZE_SMALL);
			add_paragraph(p2, "The images still felt a bit empty and lacking of details, so I took inspiration from some prints and I tried to see what all them had in common. One element that was almost always present is a big saturated circle representing the Sun (or the Moon, depending from the colors and interpretations).");
			add_paragraph(p2, "After some experiments I found that drawing it pretty flat with only a small darker border around it was the more pleasing way to render it on the canvas, keeping in mind that the sky/ground gradient was still on top of it.");
			add_paragraph(p2, "The color for the Sun/Moon is derived from the opposite of the sky/ground gradient hue to give the image a nice contrast and balance.");
			add_image3(p2, "sun0.png", "sun1.png", "sun2.png");
			add_header(p2, "Creating some stability", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Mountains are another key protagonists in many Japanese artworks and panoramas. A big centered mountain also gave a lot of balance to the artworks by filling the space evenly.");
			add_paragraph(p2, "So, to create the mountain shape I took advantage of my toolbelt functions for paths like the dispose and chaikin smoothing ones. Then the shape was filled by a gradient to blend it to the background.");
			add_image3(p2, "mountain0.png", "mountain1.png", "mountain2.png");
			add_image(p2, "mountain-sun-tree.png");
			add_header(p2, "Signing the series", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Since I'm slowly studying Japanese in my free time, I wanted to keep following these Japanese vibes and sign it using the Katakana alphabet (one of the three Japanese alphabet and the one used mainly for foreign words).");
			add_paragraph(p2, "I'm really happy with this results and I think that this is a good milestone for me and the style I'll use in my next works.");
			add_gallery(p2, 6, "Scorci 137931.png", "Scorci 991060.png", "Scorci 606684.png", "Scorci 313858.png", "Scorci 263414.png", "Scorci 214396.png");
		}

		{
			Page* p2 = create_page(p1, "Spring Flowers");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "First study on procedurally generated trees.");
			add_preview_image(p2, "Spring Flowers 964762.png");
			add_paragraph(p2, "Spring is by far my favorite season of the year both for the warm clean air and for the beautiful show that trees create for us with their flowers.");
			add_paragraph(p2, "The idea for this series came by watching a tree right in front of my house. After few times passing beside it each day going to work, I thought that these branches and flowers could be recreated by some code and functions in Clojure quite nicely.");
			add_header(p2, "The style", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Once the idea was there, it was time to choose a way to represent that object into the canvas. This wasn't a hard choice to make, since as soon as I decided to try draw some trees, it instantly come to my mind the Japanese woodblock prints with their simplicity, style, and colors.");
			add_header(p2, "The process", HEADER_SIZE_SMALL);
			add_paragraph(p2, "This series started with some path studies. The path structure present inside generative-toolbelt was a nice start, but a simple disposed line wasn't good enough to emulate the flow and curves of the tree's branches. ");
			add_image(p2, "twig0.png");
			add_paragraph(p2, "After some rework on the path generation, a decent twig-like path was ready to grow to a larger tree. The next thing was to make the branch split into smaller sub-branches in certain point of the path. After some troubles calculating the right angle to make the minor branches, the main branch generator function was ready to be reused many more times.");
			add_image3(p2, "twig1.png", "twig2.png", "twig3.png");
			add_paragraph(p2, "Once this was done, it was time for a lot of parameter tweaking. Often you can get a totally different look and feel from some piece of code by simply changing few arguments, if the code is well made and parametric.");
			add_image2(p2, "branches0.png", "branches1.png");
			add_image2(p2, "branches3.png", "branches4.png");
			add_paragraph(p2, "Last but not least, the touch of spring. This will transform those spooky and naked branches into a well dressed and colorful tree. The flowers has been realized with a rose function with n=5 and d=2. I choose a regular function to give the flowers a \"mathematical\" touch that contrast well with the realistic randomness of the branches. ");
			add_image2(p2, "flowers1.png", "flowers0.png");
			add_paragraph(p2, "With the flower in place, the base of the series generation was almost done. A few touches here and there to smooth out some rough edges and I was happy enough to create some high resolution images for the series. ");
			add_header(p2, "There is more", HEADER_SIZE_SMALL);
			add_paragraph(p2, "I'm really happy with the result so far. I'm releasing this series as it is, but I feel that I can study this tree concept much more than this, so probably I'll keep working on this to expand and improve the style and composition of the artwork.");
			add_gallery(p2, 6, "Spring Flowers 964762.png", "Spring Flowers 517361.png", "Spring Flowers 823523.png", "Spring Flowers 422983.png", "Spring Flowers 461346.png", "Spring Flowers 345016.png");
		}


		{
			Page* p2 = create_page(p1, "Deep Stars");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "Studies on Quil blends and shapes.");
			add_preview_image(p2, "Deep Stars 636364.png");
			add_header(p2, "More Chaikin experiments", HEADER_SIZE_SMALL);
			add_paragraph(p2, "In other posts I talked about the Chaikin algorithm, a beautiful piece of code to make really cool and interesting curved lines. I felt that there was much more to explore and learn from those curves so I kept working and experimenting with that. At first I tried a more minimalist version of " SENDTEXT("color_mountains", "Color Mountains") " with simple pure Chaikin lines distorted with some incremental noise repeated on each line.");
			add_image(p2, "lines0.png");
			add_paragraph(p2, "The result was really chaotic but I felt some kind of harmony from the repeated distortions. To try to make the image more readable I reduced the lines count and added a fill color inside each couple of lines to create full shapes.");
			add_image3(p2, "lines1.png", "lines2.png", "lines3.png");
			add_paragraph(p2, "Aesthetically the result was really cool to me, but it felt pretty limited so I decided to revisit the concept of repetition with additive shades.");
			add_image3(p2, "shades0.png", "shades1.png", "shades2.png");
			add_paragraph(p2, "After some trouble with my shapes drawing function not adding light alphas correctly, I managed to make it work. I used that function with concentric elliptical shapes to create the figure displayed in Shades 2. I found that composition really interesting since it could be seen in two way:");
			char* l1 = "From top to bottom it gave me a sense of depth, like the feel when you look down a deep lake from the surface.";
			char* l2 = "From bottom to top it gave me a sense of height, like the feel when you look into a clear night sky full of stars.";
			add_list(p2, false, 2, l1, l2);
			add_header(p2, "Deep Stars", HEADER_SIZE_SMALL);
			add_paragraph(p2, "That mix of contrasting feeling hooked my interest and made me try expand that concept more into the artwork.");
			add_paragraph(p2, "The next logical step was to add color.");
			add_image2(p2, "shades3.png", "shades4.png");
			add_paragraph(p2, "My old canvas-like texture didn't really fit the mood of the artwork I was looking for, so I tried a bit more random and interesting texture. The final look was achieved with the generation of many random ellipses inside and outside the canvas.");
			add_image3(p2, "texture0.png", "texture1.png", "texture2.png");
			add_paragraph(p2, "At first I tried to draw circles on random points of the main lines in order to create all the stars of the sky, the main conceptual sketch was something like these:");
			add_image(p2, "sketch0.png");
			add_paragraph(p2, "Which was then translated into a more refined style with the new texture, colors, and lines into the final series called \"Deep Stars\", which you can see all its pieces at full resolution down below.");
			add_gallery(p2, 5, "Deep Stars 636364.png", "Deep Stars 861183.png", "Deep Stars 385254.png", "Deep Stars 192731.png", "Deep Stars 513121.png");
		}

		{
			Page* p2 = create_page(p1, "Color Mountains");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "Part of my earliest studies on Quil blends.");
			add_preview_image(p2, "Color Mountains 002715.png");
			add_header(p2, "", HEADER_SIZE_SMALL);
			add_paragraph(p2, "A beautiful aspect of generative art is that you always start from the (almost) absolute zero, and as the times goes on you build a set of functions around you that stores all the various things you tried and let you create your own art (and code) style.");
			add_paragraph(p2, "This toolbelt of methods is made of lines, triangles, paths, shapes, debug functions, rendering tricks... Pretty much anything. With time, this let you build a structure to ease out your future works by quite a lot, giving you also more resources to create bigger and more complex artworks. I recently changed my whole workflow, so I had to start from the ground up once again with an empty toolbelt.");
			add_paragraph(p2, "Right now I already create all the most basic and useful function to do the simpler shapes and lines, but I was still lacking of some sort of path smoothing system for my drawings. So, these weeks I played with a wonderful algorithm to approximate curves in a very neat and elegant way called " LINKTEXT("http://graphics.cs.ucdavis.edu/education/CAGDNotes/Chaikins-Algorithm/Chaikins-Algorithm.html", "Chaikin\'s Algorithm for curves") ". I instantly fell in love with this algorithm because it can be tuned and modified in such interesting ways that can give your curves an unique and cool look.");
			add_paragraph(p2, "The algorithm has very distinct iteration steps, so I can easily draw each of its sub-iterations to give a more complex and detailed look to the lines.");
			add_image2(p2, "chaikin0.png", "chaikin1.png");
			add_image2(p2, "chaikin2.png", "chaikin3.png");
			add_paragraph(p2, "With slight randomization of the Chaikin parameters, you can give each line a more impredictable outcome.");
			add_image3(p2, "params0.png", "params1.png", "params2.png");
			add_image2(p2, "line0.png", "line1.png");
			add_image3(p2, "lines0_1.png", "lines1_1.png", "lines2_1.png");
			add_paragraph(p2, "Since each line is an array of points, those can be easily converted into paths describing 2D shapes.");
			add_image2(p2, "shape0.png", "shape1.png");
			add_paragraph(p2, "While experimenting with parameters, I even found out this \"little happy accident\" (Bonus points to who get this quote): when you use a Chaikin parameter greater than 0.5 and crank up the iterations count, the system creates a fractal like pattern inside each path's vertex.");
			add_image2(p2, "shape2.png", "shape3.png");
			add_paragraph(p2, "A unique shape gradient and blending can be achieved given the randomization and the iterative nature of the algorithm.");
			add_image2(p2, "shape4.png", "shape5.png");
			add_image2(p2, "shape6.png", "shape7.png");
			add_paragraph(p2, "I really like how these shapes blends between each others and the background, so, after some experiment on various set of shapes and colors I found this style very pleasing and cool looking to give it some more work and polish.");
			add_paragraph(p2, "The following images are few results of this work, which I called \"Color Mountains\" Series.");
			add_gallery(p2, 8, "Color Mountains 002715.png", "Color Mountains 006869.png", "Color Mountains 045739.png", "Color Mountains 109611.png", "Color Mountains 149474.png", "Color Mountains 479907.png", "Color Mountains 739953.png", "Color Mountains 952702.png");
		}
	}



////////////////////////////
// Programs
////////////////////////////
	{
		Page* p1 = create_page(p0, "Programs");
		add_paragraph(p1, "This section holds every coding project of decent sizes. Often I try to make things Open Source and available on GitHub, but it's not always true, especially for older projects and for the ones I code with other people.");


		{
			Page* p2 = create_page(p1, "ElkiwyArt");
			set_status(p2, STAT_ONGOING);
			add_preview_description(p2, "An Open-source static website builder written in C99.");
			add_preview_image(p2, "elkiwyart-c99.png");
			add_paragraph(p2, "This project is the piece of code responsible for the generation of this very website.");
			add_paragraph(p2, "The first implementation of ElkiwyArt was made mainly with PHP, a simple database, and some HTML templates. This was fine at the beginning, but it quickly became pretty hugly to improve and not really that flexible. PHP started to give errors when I was uploading new articles through forms and it was a pain to handle the creation of new posts.");
			add_paragraph(p2, "So, after I was almost abandoning the website I went through the \"Oscean\" project from Devine Lu Linvega.");
			add_paragraph(p2, "He did his website with a C99 building every page statically. That approach is ideal if you don't have dynamic pages in your website since it let you forget about PHP servers, MySQL servers, Templates, post forms, and all that crap.");
			add_paragraph(p2, "This let me focus on the only thing I want to do: create simple static pages for my website and adding anything I want.");
			add_header(p2, "The implementation", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Ok, but how the crap you write a website with C? the answer is pretty simple: you don't.");
			add_paragraph(p2, "In fact, with C99 you make a program that parse some structs you define and outputs on files simple and plain HTML tags. This is beautiful because you have the change to make your own functions to parse data and output contents in a similar way you do with Templates, but on a much more precise way.");
			add_paragraph(p2, "After you made the builder you can fill it with data in any way you want, I used another C file where I call my functions directly, but you can use JSON, YAML, or any other thing to insert data in your program.");
			add_paragraph(p2, "With builder and content in place, another beauty of this method is visible: you can check the result and your entire website locally with just a normal browser! Since everything is plain HTML there is no need for webservers and database to work. Once the result is just like you desire, you can then upload the entire generated files into your web space and it's done.");
			add_paragraph(p2, "This is a friction less system compared to my previous one and it's way easier to correct, tweak and improve the website.");
			add_header(p2, "The source", HEADER_SIZE_SMALL);
			add_paragraph(p2, "As I state before, this project is heavily inspred by Devine's work, but I rewrote almost everything to be able to understand it and customize more easily. My version is a bit simpler and essential because I still have to add some of the feature I want, but you should be able to understand the core and learn from it enough to be able to recreate a custom version for your needs.");
			add_paragraph(p2, "The full source is available on my GitHub here: " LINKTEXT("https://github.com/elkiwy/elkiwyart", "Source") ".");
			add_image(p2, "elkiwyart-c99.png");
		}

		{
			Page* p2 = create_page(p1, "Gisp Editor");
			set_status(p2, STAT_ONGOING);
			add_preview_description(p2, "A simple program to edit and run Gisp files written in Electron and ClojureScript.");
			add_preview_image(p2, "gisp-editor-thumb.png");
			add_paragraph(p2, "When my project " SENDTEXT("gisp", "Gisp") " started to take shape and be usuable to create generative art I started to feel the need for a tool to integrate the workflow and avoid having a bunch of programs open on my desktop and jump between here and there to generate art. It kinda breaks the flow when trying to be creative.");
			add_paragraph(p2, "So I started to work on a simple, yet functional, editor to work with the Gisp language being able to write Gisp code, call the interpreter to execute it, and visualize the preview of the generate image right in the editor.");
			add_image(p2, "gisp-editor-big.png");
			add_paragraph(p2, "This project is still more like a learning experiment than an actual full featured editor since I'm trying to build every feature from scratch by myself. The program is built with Electron and Clojurescript, and even the code editor is pretty bare bones I started from an editable div and I'm trying to make it work like a normal text editor.");
			add_paragraph(p2, "Currently the project is on pause because I'm working on the builder for this site in C99, but when I'll finish that I'll probably get back at this one and I might replace my crappy editor from scratch and use some other javascript open source editors to be able to focus my energy on the Gisp integration instead.");
			add_reference(p2, "Gisp-Editor Repository", "https://github.com/elkiwy/gisp-editor");
			add_reference(p2, "Gisp Repository", "https://github.com/elkiwy/gisp");
			add_reference(p2, "CLJS + Electron base project", "https://github.com/Gonzih/cljs-electron");
		}

		{
			Page* p2 = create_page(p1, "Gisp");
			set_status(p2, STAT_ONGOING);
			add_preview_description(p2, "A Graphic-oriented lisp dialect written in C and Cairo lib for drawing.");
			add_preview_image(p2, "gisp-test.png");
			add_paragraph(p2, "My journey to find the perfect setup for digital generative art is pretty long, but now it may have come to an end with Gisp, the tool I made and I'm using at the moment.");
			add_paragraph(p2, "Gisp is a Lisp dialect I made 100% focussed on giving the right tools to generate procedurally images.");
			add_image(p2, "gisp-test.png");
			add_paragraph(p2, "The core program is written in C and it consists in a lisp interpreter that reads a .gisp code file and execute it.");
			add_paragraph(p2, "For the core interpreter structure I used " LINKTEXT("https://carld.github.io/2017/06/20/lisp-in-less-than-200-lines-of-c.html", "this article") " as a great reference that explain everything you need to create your own little interpreter. It's not too advanced and very minimalistic, but I like it that way and give me freedom to expand it by myself in any way I want.");
			add_paragraph(p2, "Right now the project is pretty stable and capable of generating images, but this doesn't mean that is prefect.");
			add_paragraph(p2, "It still lacks of: ");
			char* l1 = "Proper error checking system to be able to give you insights when something in your code is wrong.";
			char* l2 = "Garbage collection and memory management.";
			char* l3 = "A REPL to continuously evaluate code and interact live with it.";
			char* l4 = "More advance graphics primitive.";
			char* l5 = "Extended Gisp core library.";
			add_list(p2, false, 5, l1, l2, l3, l4, l5);
			add_paragraph(p2, "The project also has a companion project called " SENDTEXT("gispeditor", "Gisp Editor") " which, as the name implies, is a tool to edit and run gisp code without having to manually run from the terminal.");
			add_reference(p2, "Lisp in less than 200 lines of C", "https://carld.github.io/2017/06/20/lisp-in-less-than-200-lines-of-c.html");
			add_reference(p2, "Cairo Lib", "https://www.cairographics.org");
			add_reference(p2, "Gisp Repository", "https://github.com/elkiwy/gisp");
			add_reference(p2, "Gisp-Editor Repository", "https://github.com/elkiwy/gisp-editor");

			{
				Page* p3 = create_page(p2, "Documentation");
				set_status(p3, STAT_TOSTART);
				add_preview_description(p3, "Documentation and API reference for Gisp");
				add_header(p3, "Reference", HEADER_SIZE_SMALL);
				add_stub(p3, "Autogenerated reference");
			}
		}


		{
			Page* p2 = create_page(p1, "PaYnter");
			set_status(p2, STAT_PAUSED);
			add_preview_description(p2, "A Python module to procedurally generate images using tools that emulates image editing software tools.");
			add_preview_image(p2, "paynter1.png");
			add_header(p2, "The journey", HEADER_SIZE_SMALL);
			add_paragraph(p2, "I started to make proper generative art with a little python script to automate mouse and keyboard input to interact with Krita, a digital drawing tool. I like the complexity of the brushes and all the tool available inside Krita, but after few generations it started to feel pretty hacky and uncomfortable to use.");
			add_paragraph(p2, "So after that I wanted to try and replicate the brushes and complexity of an image editing software by myself by making a python program that emulated that. That was the birth of PaYnter.");
			add_paragraph(p2, "The main features of PaYnter are:");
			add_header(p2, "Brushes emultation", HEADER_SIZE_SMALL);
			add_paragraph(p2, "With paynter you draw on your digital image with brushes just like you do on Photoshop. You can create brushes starting from images defining the brush tip, and then you can define a bunch of brush parameters like:");
			char* l1 = "Size";
			char* l2 = "Spacing";
			char* l3 = "Angle";
			char* l4 = "Color mixing";
			char* l5 = "Hue";
			char* l6 = "Saturation";
			char* l7 = "Color Value";
			char* l8 = "Random position offsetting";
			add_list(p2, false, 8, l1, l2, l3, l4, l5, l6, l7, l8);
			add_header(p2, "Layer management", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Each image is composed by one or multiple layers. Each layer interally is one 3D array of [imageWidth * imageHeight * 4] to store the RGBA value of each pixel of the layer.");
			add_paragraph(p2, "When drawing you specify on which layer you are using, and then when you are done with the editing you can then merge all the layers using various blend modes to create many different effects.");
			add_header(p2, "Palette management", HEADER_SIZE_SMALL);
			add_paragraph(p2, "You can choose color individually or use one of the PaYnter preset palette generation where you can specify some starting values and generate opposite or complementary colors from the starting one.");
			add_paragraph(p2, "Each color can then be tweaked individually from saturation, hue, and value.");
			add_image2(p2, "paynter1.png", "paynter2.png");
			add_image(p2, "paynter3.png");

			add_paragraph(p2, "The project got discontinued when I realize that it was too slow and, even through many optimization iterations the performance wasn't enough for my needs. I used a lot of matrix operation which could have been optimized a lot by using the GPU, but sadly it seems that all the decent framework for that uses nVidia drivers and I don't have a nVidia GPU, so that was not an option.");
			add_reference(p2, "PaYnter Documentation", "https://paynter.readthedocs.io/en/latest/");
		    add_reference(p2, "PaYnter Repository", "https://github.com/elkiwy/paynter");
		}



		{
			Page* p2 = create_page(p1, "RaspberryWallet");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "A simple set of python scripts to handle wallet transactions through Telegram bot and Google Spreadsheet.");
			add_preview_image(p2, "raspwallet.png");
			add_header(p2, "The idea", HEADER_SIZE_SMALL);
			add_paragraph(p2, "This is one of my earliest project and my first one on my Raspberry Pi. Today I'm thinking of deprecating it and rebuild a much more structured and better alternative to it with one my friend.");
			add_paragraph(p2, "RaspberryWallet aims to be one simple solution to keep track of all my income and outcome for my finances.");
			add_paragraph(p2, "The most important feature I wanted from this project is to be accessible from anywhere in anytime, and the better thing I though was to create it on top of a Telegram Bot, so anywhere I have access to Telegram I can use it.");
			add_paragraph(p2, "This turned out to be a great idea since I can use it as soon as I spend some money in few seconds by sending a simple message.");
			add_header(p2, "The workflow", HEADER_SIZE_SMALL);
			add_paragraph(p2, "The flow is this:");
			char* l1 = "I send a message to my bot with the amount of money spent or earned and a description";
			char* l2 = "The bot, after verify that the message is from my account, parse it with a python script";
			char* l3 = "The script connects to a Google Spreadsheet and insert a new row into a sheet.";
			char* l4 = "Another sheet then takes the data from the first sheet and present the data in a nice way.";
			add_list(p2, true, 4, l1, l2, l3, l4);
			add_paragraph(p2, "This works somewhat decently, but is nowhere near the ideal way to handle this kind of problems.");
			add_paragraph(p2, "Right now I'm still using this since it works, but soon I'll make it from scratch again with a totally different approach.");
		}
	}



////////////////////////////
// Games
////////////////////////////
	{
		Page* p1 = create_page(p0, "Games");


		{
			Page* p2 = create_page(p1, "Hull Breach");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "A game about repairing a spaceship trying to escape from bad guys through an asteroids belt.<br>Made with Pico8 for GlobalGameJam2020.");
			add_preview_image(p2, "hullbreach3.png");
			add_paragraph(p2, "HullBreach was developed in the Globalgamejam2020 by me and Alberto, one friend of mine that always do game jams with me.");
			add_paragraph(p2, "The theme of the jam was <b>\"Repair\"</b> and we choose to use Pico8 as our game engine for the jam.");
			add_paragraph(p2, "The core gameplay is pretty simple, but the adventure in making it is pretty interesting and quite a challenge.");
			add_header(p2, "The Sketch", HEADER_SIZE_SMALL);
			add_paragraph(p2, "After the jam theme announcement (which was Repair) we started to sketch out ideas on what kind of game to make. Those were plenty: a coop tetris-puzzle-builder, a cyborg brawler multiplayer, a motherboard repair simulator, and other. All those ideas were decent but not fully satisfying to us. Then we stumbled on an idea about managing the repair of a spaceship where each one of its pixel was simulated. That sounded instantly the right idea and we started right away.");
			add_paragraph(p2, "So, the main design consisted in a spaceship going somewhere in space escaping from some sort of bad guy that is shooting lasers at you while you go through an area full of asteroids. The ship can self-repair from the damage by creating healing drones from its core, but you have to tell the drones which materials (colors of the pixel) they have to repair.");
			add_paragraph(p2, "The Jam started Friday around 18:00 and in the early hours of Saturday morning (around 6am) we already had the final design of the spaceship, a damage system where you could click to create a hole in the shell, and an early version of the repairing bots to fix the damaged pixels.");
			add_paragraph(p2, "The code was pretty brutal and rough but working, and that was fine for a jam… Fine until we hit the Pico8 memory and CPU limitation so hard that we couldn't add more cool feature because of that. It was time for some optimization.");
			add_paragraph(p2, "I spent almost the entire Saturday trying to find a way to compress and rearrange all the main data structure into a smaller and more performing one.");
			add_paragraph(p2, "<b>NB: This is not a guide on \"The perfect way to handle data\" or anything like that.</b> I just wanted to document my thought process during a game jam. There are way less complicated way to design data structures better than this, but I found this journey very interesting and a cool learning experience.");
			add_header(p2, "First Iteration", HEADER_SIZE_SMALL);
			add_paragraph(p2, "The first iteration was a 128x128 array containing data for each pixel on the screen. The pixel needed to hold its position, color, status, and a flag for the bot spawn point. This alone was:");
			char* l1 = MONOSPACE("128 width x 128 height = 16'384 cells");
			char* l2 = MONOSPACE("16384 cells x 5 numbers = 81'920 numbers");
			char* l3 = MONOSPACE("81920 numbers x 4 byte = 327'680 bytes");
			add_list(p2, false, 3, l1, l2, l3);
			add_paragraph(p2, "<i>(I could have used true/false instead of 0 and 1 for flags, but that wouldn't have changed much because in this stage of design those wasn't really only 2 states flags)</i>");
			add_paragraph(p2, "320 Kb for the raw data inside a single structure is way too much for pico to handle.");
			add_paragraph(p2, "Another big problem was that in order to draw each pixel the cpu was cycling every cell and calling PSET to draw a pixel on screen, and that was really taxing on the CPU time.");
			add_header(p2, "Second Iteration", HEADER_SIZE_SMALL);
			add_paragraph(p2, "The first improvement of that was to move the 2d array into a single array with only the point needed to draw the ship, so the number of cells dropped from 16'384 to somewhere around 5'000. That was really good for the drawing performance, but had a big drawback: single point checking for specific X and Y.");
			add_paragraph(p2, "In fact, with the 2D array it was really easy to get the information of a single point knowing its coordinates because the time to get that information was really small and constant, no cycling needed.");
			add_paragraph(p2, "On the other hand, having a 1D array of non-ordinated points was exponentially slower since you needed to cycle all the point until you find some point with its coordinates equals to the one you needed.");
			add_paragraph(p2, "The single point access was pretty much crucial to us since we wanted to add A-star pathfinding algorithm for the repair bots and for other things inside the game.");
			add_header(p2, "Third Iteration", HEADER_SIZE_SMALL);
			add_paragraph(p2, "We had to somehow get back at a 2D data structure design, but we had to forget the standard way of doing it.");
			add_paragraph(p2, "After some research on the Pico8 memory layout I found out that it manage its memory in two way: the variables allocated in the code while the game is running uses a special Lua memory which is limited to around 2MB; but there is also the cart RAM which is used by all the cart assets (sprite, map layout, sfx, music, etc). This last one can be used to store extra arbitrary data.");
			add_paragraph(p2, "So I started to layout some of the memory I needed to move it there while trying to compressing it into the smallest space I could.");
			add_paragraph(p2, "Pico8 default integer size is 32 bit long: 16bit for the integer part and 16 for the floatin one.");
			add_paragraph(p2, "That's pretty huge in memory if you only need small integer numbers. The numbers I needed theoretically were:");
			char* r1 = MONOSPACE("1 bit integers for true/false flags");
			char* r2 = MONOSPACE("4 bit integers to store the color value of a pixel (numbers from 0 to 15)");
			add_list(p2, false, 2, r1, r2);
			add_paragraph(p2, "So, knowing that the single memory registers in Pico8 are 1 byte long (8 bit), I could \"easily\" compress 1 color value (4 bit) and 4 boolean flags into a single 1 byte register.");
			add_paragraph(p2, "I put quotes on easily, because it really wasn't so easy since it was the first time I was trying to do something like that. The ideal layout was indeed pretty straightforward, but I had to make some custom getters and setters to use from Pico8 to be able to store/read that compressed number to/from memory. That required some bit-wise logic and operations.");
			add_paragraph(p2, "After some fiddling with that, around 5pm, it was ready. The memory usage dropped significantly to \"only\":");
			char* m1 = MONOSPACE("128 width x 128 width = 16'384 cells");
			char* m2 = MONOSPACE("16'384 cells = 16'384 bytes");
			add_list(p2, false, 2, m1, m2);
			add_paragraph(p2, "From 327'680 to 16'384 bytes is not a bad improvement, but we could do better than that. In fact, even if it was an huge improvement, it moved from the Lua memory to the Pico8 cartridge memory, and that gave some issues.");
			add_paragraph(p2, "The cartridge memory layout is this:");
			char* n1 =  MONOSPACE("0x0000 to 0x0fff — Sprite sheet (0-127)");
			char* n2 =  MONOSPACE("0x1000 to 0x1fff — Sprite sheet (128-255) / Map (rows 32-63) (shared)");
			char* n3 =  MONOSPACE("0x2000 to 0x2fff — Map (rows 0-31)");
			char* n4 =  MONOSPACE("0x3000 to 0x30ff — Sprite flags");
			char* n5 =  MONOSPACE("0x3100 to 0x31ff — Music");
			char* n6 =  MONOSPACE("0x3200 to 0x42ff — Sound effects");
			char* n7 =  MONOSPACE("0x4300 to 0x5dff — General use (or work RAM)");
			char* n8 =  MONOSPACE("0x5e00 to 0x5eff — Persistent cart data (64 numbers = 256 bytes)");
			char* n9 =  MONOSPACE("0x5f00 to 0x5f3f — Draw state");
			char* n10 = MONOSPACE("0x5f40 to 0x5f7f — Hardware state");
			char* n11 = MONOSPACE("0x5f80 to 0x5fff — GPIO pins (128 bytes)");
			char* n12 = MONOSPACE("0x6000 to 0x7fff — Screen data (8k)");
			add_list(p2, false, 12, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12);
			add_paragraph(p2, "As you can see the whole pico8 memory is 32kb and it's shared between important cartridge data like sprite information, music, sounds, etc. We currently have 16k to fill in somewhere and the \"General use memory\" is only 6kb, so I needed to override some sprite sheet memory and map data to make it fit in. One minor problem was that even overriding sprite data I had to \"jump\" music and SFX memory to make it fit.");
			add_paragraph(p2, "So I decided to use all the 11kb from 0 to 0x2fff and from 0x4300 to 0x5dff. It was very ugly but it worked.");
			add_header(p2, "Fourth Iteration", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Then, suddently after the saturday dinner break, I realized one thing: I was trying to manage all the colors for each pixel on the spaceship sprite by myself, but Pico8 already does that for its spritesheet in the 0x0000 - 0x1fff memory space!");
			add_paragraph(p2, "I felt particularly dumb. Pico stores that information by using 1 byte for 2 pixels since the color information is only 4 bits and the memory registers are 8 bit long. That was better than what I was trying to do, so I start thinking if I could cut down that information and only store my extra data (3 boolean flags).");
			add_paragraph(p2, "I realized that we could cut down one flag by changing the code slightly, so with only 2 boolean per pixel I could store 4 pixel into a single byte by using each bit as an individual flag.");
			add_paragraph(p2, "Leftmost 4 bits are for flag A and rightmost 4 bits are for flag B Example:");
			char* t1 = MONOSPACE("0000 0000 => all flags are false");
			char* t2 = MONOSPACE("1000 1000 => first pixel has flag A and B true, other 3 pixels has both flags on false");
			char* t3 = MONOSPACE("0100 1100 => flag A is set for second pixel, flag B is set for first and second pixels");
			add_list(p2, false, 3, t1, t2, t3);
			add_paragraph(p2, "This way I could squeeze all my information like:");
			char* a1 = MONOSPACE("128 width x 128 width = 16'384 cells");
			char* a2 = MONOSPACE("16'384 cells / 4 cells for bytes = 4'096 bytes");
			add_list(p2, false, 2, a1, a2);
			add_paragraph(p2, "With only 4kb I could fit that into the General use memory space with no need of overriding important data!");
			add_paragraph(p2, "In conclusion, after doing all this madness (the real pain was coding the getters and setters for those bit flags, but I'll not go into those details here since this post is already quite long) we were able to have both single point direct access to data AND we can create an array of memory pointers to focus down only important data.");
			add_header(p2, "Conclusion", HEADER_SIZE_SMALL);
			add_paragraph(p2, "With all this in place we finished the rest of the game on Sunday. The final game was \"ok\". We had fun making it, it's cool to watch, but the gameplay could be better.");
			add_paragraph(p2, "Overall, it was a great event and is always nice to be part of it. Everyone interested in games should try that to push their limits and learn bunch of new things in an unique experience!");
			add_reference(p2, "GlobalGameJam Page", "https://globalgamejam.org/2020/games/hull-breach-4");

		}
		{
			Page* p2 = create_page(p1, "BuildTutto");
			set_status(p2, STAT_SUSPENDED);
			add_preview_description(p2, "A deep resource management building and crafting game.<br>Made with C++ and Allegro.");
			add_preview_image(p2, "buildtutto1.png");

			add_paragraph(p2, "After I finished University I wanted to dedicate to game developing again. After the BeardedBear suspension I wanted to do something different and all by myself.");
			add_paragraph(p2, "At the time I was playing a lot games like Prison Architect, Rimworld, Factorio, Dwarf fortress, and other resource mangement game. So I wanted to do my own game.");

			add_header(p2, "The Idea", HEADER_SIZE_SMALL);
			add_paragraph(p2, "\"Tutto\" means \"everything\" in italian, so the title kinda explain what the game is about.");
			add_image_desc(p2, "buildtutto_pipes.png", "A test environment for verify objects interactions.");
			add_paragraph(p2, "In BuildTutto the main goal is to build and manage a company that creates factories. There are a lot of micromanagement aspects into the building creation like water piping, electring cables layout, lights, structural strenght, weight and more.");
			add_paragraph(p2, "On top of all that, the player need to research and create every object starting from raw materials. <b>Every</b> object can be made from <b>any</b> materials or part, and that final object inherits the fundamental properties of its components.");
			add_paragraph(p2, "An example could be the electric cable object. It can be made of copper with a proper electric conductivity, but it can also be made from wood or concrete and have very low or zero electric conductivity. This is an absurd example, but it should explain the concept.");
			add_image_desc(p2, "buildtutto_blueprint.gif", "Blueprint window to research and create new objects.");
			add_paragraph(p2, "I spent a lot of time researching physical properties of elements and metals to try to be the most accurate possible and give the player a great choice when planning his buildings.");
			add_paragraph(p2, "After blueprinting all the object needed, the player has a group of workers available to build anything he wants.");
			add_image_desc(p2, "buildtutto_unload.gif", "The workers unloading the truck with the raw resources.");

			add_header(p2, "The tech", HEADER_SIZE_SMALL);
			add_paragraph(p2, "After having played around a lot with GameMaker I wanted to try something different. Also, I was scared that a game like that was too taxing for gamemaker, so I decided to teach myself C++ through this project.");
			add_paragraph(p2, "I was interested in learning OpenGL too, but probably it would have been too much to learn in one project. So I decided to use " LINKTEXT("https://liballeg.org", "Allegro") " as the main graphics and input library. I choose it after reading that Factorio developers used it, so I thought \"If that can make a game like Factorio it should be more than enough for me\". Of course after one month from the beginning of the development they published another post where they explained why they migrated from Allegro to SDL2, but it was still good enough for me and I kept working with that.");
			add_paragraph(p2, "It was also the first time using Visual Studio and, to my surprise, it was really good to debugging when something was going wrong. I also like a lot programming with just an editor and a terminal to compile, so I usually sticked with that to program features and then switch to Visual Studio to debug those.");
			add_image_desc(p2, "buildtutto_darkness.gif", "The dynamic lighting of the rooms and roof structural support testing.");

			add_header(p2, "The implementation", HEADER_SIZE_SMALL);
			add_paragraph(p2, "Working on that was great, it was very satisfing and I was often working with my friends in libraries or university public areas. It was very productive for me to not being alone in my room.");
			add_paragraph(p2, "After almost one year of development the project was starting to feel heavy while going inevitably out of scope for a single person doing all the programming, art, and design.");
			add_paragraph(p2, "My family went through some financial problems too, so I couldn't afford to work on that without an income. Since if was still very very far from a final product I couldn't hope to make a living out of it, so I had to suspend the project after starting a full time developer job.");

			add_header(p2, "The devlog", HEADER_SIZE_SMALL);
			add_paragraph(p2, "If you are curious and you want more information about the game I was doing a thing where every week I posted on " LINKTEXT("https://www.indiedb.com/games/project-buildtutto","IndieDB") ", so you can find a lot of details on what I was working and how I was doing it.");
			add_image_desc(p2, "buildtutto_pipestoassembler.gif", "Workers building pipes from raw materials.");

			add_reference(p2, "Allegro Lib", "https://liballeg.org");
			add_reference(p2, "IndieDB Page", "https://www.indiedb.com/games/project-buildtutto");
			add_reference(p2, "Devlog timelapses", "https://www.youtube.com/channel/UC2l3kcw6wUn4Z1-cr5UMLMw");
		}
		{
			Page* p2 = create_page(p1, "WaveJump");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "A local multiplayer game about crating and jumping on waves to kill your opponent.<br>Made with Gamemaker for the GlobalGameJam2017.");
			add_preview_image(p2, "wavejump1.png");
			add_reference(p2, "GlobalGameJam Page", "https://globalgamejam.org/2017/games/wavejump");
			add_reference(p2, "Itch.io Page", "https://bearsinmind.itch.io/wavejump");
		}
		{
			Page* p2 = create_page(p1, "AsciiRush");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "A score-attack speedcrafting ascii game with an abuse of post rendering effects.<br>Made with Gamemaker.");
			add_preview_image(p2, "asciirush1.png");
			add_reference(p2, "Itch.io Page", "https://bearsinmind.itch.io/asciirush");

		}
		{
			Page* p2 = create_page(p1, "BeardedBear");
			set_status(p2, STAT_SUSPENDED);
			add_preview_description(p2, "A game about a bear with a might bear shooting aliens through time and space.<br>Made with GameMaker.");
			add_preview_image(p2, "beardedbear1.png");
			add_reference(p2, "YouTube Trailer",  "https://youtu.be/7yaPZY4X-A");
			add_reference(p2, "IndieDB Page",  "http://www.indiedb.com/games/beardedbea");
			add_reference(p2, "TIGSource Thread",  "https://forums.tigsource.com/index.php?topic=54839.");

			{
				Page* p3 = create_page(p2, "Concept");
			}
			{
				Page* p3 = create_page(p2, "Iterations");
			}
			{
				Page* p3 = create_page(p2, "Suspension");
			}
		}
		{
			Page* p2 = create_page(p1, "Asafah");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "An game about a guy who wants to complete a ritual while shooting demons.<br>Made with Pico8 for GlobalGameJam2016.");
			add_preview_image(p2, "asafah1.png");
			add_reference(p2, "Gameplay trailer", "https://www.youtube.com/watch?v=fLn9B9L90zQ");
			add_reference(p2, "GlobalGameJam Page", "https://globalgamejam.org/2016/games/asafah");
		}
		{
			Page* p2 = create_page(p1, "Shootshift");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "A shooter game where you shapeshift every five action you take.<br>Made with Gamemaker for LudumDare35");
			add_preview_image(p2, "shootshift1.png");
			add_reference(p2, "Itch.io Page", "https://elkiwydev.itch.io/shootshift");
		}
		{
			Page* p2 = create_page(p1, "Get The Fick Out");
			set_status(p2, STAT_FINISHED);
			add_preview_description(p2, "Silly game about a drunk man, exploding chairs, wild fires, and far-west style saloon.<br>Made with Gamemaker for LudumDare31.");
			add_preview_image(p2, "getthefickout1.jpg");
			add_reference(p2, "LudumDare Page", "http://ludumdare.com/compo/ludum-dare-31/?action=preview&uid=40741");
			add_reference(p2, "Development Timelapse", "https://www.youtube.com/watch?v=hOjXrH4-LeQ");
		}

	}


////////////////////////////
// Strudies
////////////////////////////
	{
		Page* p1 = create_page(p0, "Other");
		add_paragraph(p1, "This section is for everything I study, research, and everything else that doesn't find a good fit in the other main categories but I still want to talk about it.");

		{
			Page* p2 = create_page(p1, "Japanese");
			add_preview_description(p2, "My studies on the Japanese Language.");
		}
		{
			Page* p2 = create_page(p1, "Emacs");
			add_preview_description(p2, "My prefered text editor and my thoughts about it.");
		}
		{
			Page* p2 = create_page(p1, "6502 Assembly");
			add_preview_description(p2, "My studies on 6502 Assembly for NES game development.");
		}
	}



////////////////////////////
// Guides
////////////////////////////
	{
		Page* p1 = create_page(p0, "Guides");
		{
			Page* p2 = create_page(p1, "Simple Hash table in C");
			add_preview_description(p2, "How to implement an Hash table from scratch in C or any other programming language.");
		}
	}


////////////////////////////
// About
////////////////////////////
	{
		Page* p1 = create_page(p0, "About");
	}

}























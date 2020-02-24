
#define LINK(url)           "<a class='link' href='"url"' class='external' target='_blank'>"url"</a>"
#define LINKTEXT(url, name) "<a class='link' href='"url"' class='external' target='_blank'>"name"</a>"

#define SEND(page)           "<a class='link' href='" page ".html'>" page "</a>"
#define SENDTEXT(page, text) "<a class='link' href='" page ".html'>" text "</a>"

#define IMAGE(name) "<img src='../media/identity/" name "'/>"
#define PAR(content) "<p>" content "</p>"


#define HEADER_SIZE_SMALL 2

////////////////////////////
// Home
////////////////////////////
Page* home = create_page(NULL, "home");
add_paragraph(home, "Welcome to ElKiwyArt website!");
add_paragraph(home, "This is my very personal attempt to show who am I, and what I do. Since I do many different things sprinkled around the internet, the scope of this website is to try group all up and present everything to you in a nice and clear way.");
add_paragraph(home, "But, this is not a portfolio where i present everything I made or released. There will also be random posts on anything I do in a particular time in my life, maybe some big project, or maybe just a little dumb study on something." );
add_image(home, "default_1080.png");
add_stub(home, "Closing");


////////////////////////////
// Art
////////////////////////////
Page* art = create_page(home, "art");
add_stub(art, "Introduzione su ART");



Page* gates = create_page(art, "Gates");
add_preview_description(gates, "Third study on procedurally generated trees, going for a more abstract and twisted shapes.");
add_paragraph(gates, "I really enjoyed the natural look of Scorci , but after that I started to want back some of the regular and geometric feel typical of generative art. So what's better than some natural-ish tree with weird geometric shapes? ");
add_header(gates, "One more tree iteration", HEADER_SIZE_SMALL);
add_paragraph(gates, "This may starts to feel a bit repetitive, but I wanted to get one more artwork with this style. The process to achieve these pieces has been pretty simple this time. I had to take the old tree function and tweak it to accept a path as input for the main trunk. Before these changes, that function was accepting just a single point and a starting direction for the tree to grow, but that had two major problems:");
char* l1 = "The final structure of the tree was not predictable. Half of the times the tree would start in the right spot, then curving out of the canvas letting me with a bunch of nothing on the screen.";
char* l2 = "I could not give the tree a fixed shape and then let the minor branches go where they wanted.";
add_number_list(gates, 2, l1, l2);
add_image(gates, "start0.png");
add_paragraph(gates, "After some changes I had something that could work for what I wanted to do:");
add_image2(gates, "straight0.png", "straight1.png");
add_paragraph(gates, "Once that the tree was following whatever the path I wanted, I had to find some nice shapes to draw.");
add_image2(gates, "rectangle0.png", "rectangle1.png");
add_image2(gates, "rectangles0.png", "rectangles1.png");
add_paragraph(gates, "The concept was there, but the idea of trees floating mid-air with no roots to keep them anchored somewhere wasn't really right for this kind of artwork, so I had to add something to give some stability to the drawing.");
add_paragraph(gates, "(Sadly I can't show this part of the process because I lost the images from that day)");
add_paragraph(gates, "After some minor tweaks the series was ready to start the full resolution generation.");
add_gallery(gates, 6 ,"Gates_96650.png" ,"Gates_617167.png" ,"Gates_619683.png" ,"Gates_932704.png" ,"Gates_141067.png" ,"Gates_965820.png");



Page* scorci = create_page(art, "Scorci");
add_preview_description(scorci, "Second study on procedurally generated trees synthesising a Japanese panorama.");
add_header(scorci, "A rework of Spring Flowers", HEADER_SIZE_SMALL);
add_paragraph(scorci, "To everyone that saw my previous posts, these new pieces could feel pretty similar to the series \"Spring Flowers\" since I reused the tree and flower structure and expanded that concept into a more complete tribute to the Ukiyo-E style Japanese woodprints.");
add_paragraph(scorci, "The previous series was pretty minimalist and plain, but this new rework aimed to give the right mood to that concept by giving more context of the surrounding of that tree.");
add_header(scorci, "Giving some space", HEADER_SIZE_SMALL);
add_paragraph(scorci, "The first thing to do was adding a Bi-Linear gradient on top of everything that shades darker on the top and the bottom of the artwork, this gives a sense of space by giving a subtle hint of where the sky, ground, and horizon line is in the canvas.");
add_paragraph(scorci, "This small detail alone already gave the artwork a totally different mood and feel.");
add_image2(scorci, "gradient0.png", "gradient1.png");
add_header(scorci, "Lighten up the image", HEADER_SIZE_SMALL);
add_paragraph(scorci, "The images still felt a bit empty and lacking of details, so I took inspiration from some prints and I tried to see what all them had in common. One element that was almost always present is a big saturated circle representing the Sun (or the Moon, depending from the colors and interpretations).");
add_paragraph(scorci, "After some experiments I found that drawing it pretty flat with only a small darker border around it was the more pleasing way to render it on the canvas, keeping in mind that the sky/ground gradient was still on top of it.");
add_paragraph(scorci, "The color for the Sun/Moon is derived from the opposite of the sky/ground gradient hue to give the image a nice contrast and balance.");
add_image3(scorci, "sun0.png", "sun1.png", "sun2.png");
add_header(scorci, "Creating some stability", HEADER_SIZE_SMALL);
add_paragraph(scorci, "Mountains are another key protagonists in many Japanese artworks and panoramas. A big centered mountain also gave a lot of balance to the artworks by filling the space evenly.");
add_paragraph(scorci, "So, to create the mountain shape I took advantage of my toolbelt functions for paths like the dispose and chaikin smoothing ones. Then the shape was filled by a gradient to blend it to the background.");
add_image3(scorci, "mountain0.png", "mountain1.png", "mountain2.png");
add_image(scorci, "mountain-sun-tree.png");
add_header(scorci, "Signing the series", HEADER_SIZE_SMALL);
add_paragraph(scorci, "Since I'm slowly studying Japanese in my free time, I wanted to keep following these Japanese vibes and sign it using the Katakana alphabet (one of the three Japanese alphabet and the one used mainly for foreign words).");
add_paragraph(scorci, "I'm really happy with this results and I think that this is a good milestone for me and the style I'll use in my next works.");
add_gallery(scorci, 6, "Scorci 137931.png", "Scorci 991060.png", "Scorci 606684.png", "Scorci 313858.png", "Scorci 263414.png", "Scorci 214396.png");



Page* spring_flowers = create_page(art, "Spring Flowers");
add_preview_description(spring_flowers, "First study on procedurally generated trees.");
add_paragraph(spring_flowers, "Spring is by far my favorite season of the year both for the warm clean air and for the beautiful show that trees create for us with their flowers.");
add_paragraph(spring_flowers, "The idea for this series came by watching a tree right in front of my house. After few times passing beside it each day going to work, I thought that these branches and flowers could be recreated by some code and functions in Clojure quite nicely.");
add_header(spring_flowers, "The style", HEADER_SIZE_SMALL);
add_paragraph(spring_flowers, "Once the idea was there, it was time to choose a way to represent that object into the canvas. This wasn't a hard choice to make, since as soon as I decided to try draw some trees, it instantly come to my mind the Japanese woodblock prints with their simplicity, style, and colors.");
add_header(spring_flowers, "The process", HEADER_SIZE_SMALL);
add_paragraph(spring_flowers, "This series started with some path studies. The path structure present inside generative-toolbelt was a nice start, but a simple disposed line wasn't good enough to emulate the flow and curves of the tree's branches. ");
add_image(spring_flowers, "twig0.png");
add_paragraph(spring_flowers, "After some rework on the path generation, a decent twig-like path was ready to grow to a larger tree. The next thing was to make the branch split into smaller sub-branches in certain point of the path. After some troubles calculating the right angle to make the minor branches, the main branch generator function was ready to be reused many more times.");
add_image3(spring_flowers, "twig1.png", "twig2.png", "twig3.png");
add_paragraph(spring_flowers, "Once this was done, it was time for a lot of parameter tweaking. Often you can get a totally different look and feel from some piece of code by simply changing few arguments, if the code is well made and parametric.");
add_image2(spring_flowers, "branches0.png", "branches1.png");
add_image2(spring_flowers, "branches3.png", "branches4.png");
add_paragraph(spring_flowers, "Last but not least, the touch of spring. This will transform those spooky and naked branches into a well dressed and colorful tree. The flowers has been realized with a rose function with n=5 and d=2. I choose a regular function to give the flowers a \"mathematical\" touch that contrast well with the realistic randomness of the branches. ");
add_image2(spring_flowers, "flowers1.png", "flowers0.png");
add_paragraph(spring_flowers, "With the flower in place, the base of the series generation was almost done. A few touches here and there to smooth out some rough edges and I was happy enough to create some high resolution images for the series. ");
add_header(spring_flowers, "There is more", HEADER_SIZE_SMALL);
add_paragraph(spring_flowers, "I'm really happy with the result so far. I'm releasing this series as it is, but I feel that I can study this tree concept much more than this, so probably I'll keep working on this to expand and improve the style and composition of the artwork.");
add_gallery(spring_flowers, 6, "Spring Flowers 964762.png", "Spring Flowers 517361.png", "Spring Flowers 823523.png", "Spring Flowers 422983.png", "Spring Flowers 461346.png", "Spring Flowers 345016.png");


Page* deep_stars = create_page(art, "Deep Stars");
add_preview_description(deep_stars, "Studies on Quil blends and shapes.");
add_stub(deep_stars, "Migrare pagina");



Page* color_mountains = create_page(art, "Color Mountains");
add_preview_description(color_mountains, "Part of my earliest studies on Quil blends.");
add_stub(color_mountains, "Migrare pagina");


////////////////////////////
// Programs
////////////////////////////
Page* programs = create_page(home, "programs");
add_paragraph(programs, "This section holds every coding project of decent sizes. Often I try to make things Open Source and available on GitHub, but it's not always true, especially for older projects and for the ones I code with other people.");



Page* elkiwyart = create_page(programs, "ElkiwyArt");
add_preview_description(elkiwyart, "An Open-source static website builder written in C99.");
add_paragraph(elkiwyart, "This project is the piece of code responsible for the generation of this very website.");
add_paragraph(elkiwyart, "The first implementation of ElkiwyArt was made mainly with PHP, a simple database, and some HTML templates. This was fine at the beginning, but it quickly became pretty hugly to improve and not really that flexible. PHP started to give errors when I was uploading new articles through forms and it was a pain to handle the creation of new posts.");
add_paragraph(elkiwyart, "So, after I was almost abandoning the website I went through the \"Oscean\" project from Devine Lu Linvega.");
add_paragraph(elkiwyart, "He did his website with a C99 building every page statically. That approach is ideal if you don't have dynamic pages in your website since it let you forget about PHP servers, MySQL servers, Templates, post forms, and all that crap.");
add_paragraph(elkiwyart, "This let me focus on the only thing I want to do: create simple static pages for my website and adding anything I want.");
add_header(elkiwyart, "The implementation", HEADER_SIZE_SMALL);
add_paragraph(elkiwyart, "Ok, but how the crap you write a website with C? the answer is pretty simple: you don't.");
add_paragraph(elkiwyart, "In fact, with C99 you make a program that parse some structs you define and outputs on files simple and plain HTML tags. This is beautiful because you have the change to make your own functions to parse data and output contents in a similar way you do with Templates, but on a much more precise way.");
add_paragraph(elkiwyart, "After you made the builder you can fill it with data in any way you want, I used another C file where I call my functions directly, but you can use JSON, YAML, or any other thing to insert data in your program.");
add_paragraph(elkiwyart, "With builder and content in place, another beauty of this method is visible: you can check the result and your entire website locally with just a normal browser! Since everything is plain HTML there is no need for webservers and database to work. Once the result is just like you desire, you can then upload the entire generated files into your web space and it's done.");
add_paragraph(elkiwyart, "This is a friction less system compared to my previous one and it's way easier to correct, tweak and improve the website.");
add_header(elkiwyart, "The source", HEADER_SIZE_SMALL);
add_paragraph(elkiwyart, "As I state before, this project is heavily inspred by Devine's work, but I rewrote almost everything to be able to understand it and customize more easily. My version is a bit simpler and essential because I still have to add some of the feature I want, but you should be able to understand the core and learn from it enough to be able to recreate a custom version for your needs.");
add_paragraph(elkiwyart, "The full source is available on my GitHub here: " SENDTEXT("https://github.com/elkiwy/elkiwyart", "ElkiwyArt C99 Source") ".");
add_stub(elkiwyart, "Continue...");



Page* raspwallet = create_page(programs, "RaspberryWallet");
add_preview_description(raspwallet, "A simple set of python scripts to handle wallet transactions through Telegram bot and Google Spreadsheet.");



Page* gisp = create_page(programs, "Gisp");
add_preview_description(gisp, "A Graphic-oriented lisp dialect written in C and Cairo lib for drawing.");



Page* paynter = create_page(programs, "PaYnter");
add_preview_description(paynter, "A Python module to procedurally generate images using tools that emulates image editing software tools.");



////////////////////////////
// Games
////////////////////////////
Page* games = create_page(home, "games");
create_page(games, "BeardedBear");
create_page(games, "BuildTutto");
create_page(games, "WaveJump");
create_page(games, "AsciiRush");
create_page(games, "Shootshift");
create_page(games, "Get The Fick Out");



////////////////////////////
// Strudies
////////////////////////////
Page* studies = create_page(home, "studies");
add_paragraph(studies, "This section is for everything I study, research, and everything else that doesn't find a good fit in the other main categories.");

create_page(studies, "Japanese");
create_page(studies, "6502 Assembly");



////////////////////////////
// About
////////////////////////////
Page* about = create_page(home, "about");

























#define LINK(url)           "<a href='"url"' class='external' target='_blank'>"url"</a>"
#define LINKTEXT(url, name) "<a href='"url"' class='external' target='_blank'>"name"</a>"

#define SEND(page)           "<a href='" page ".html'>" page "</a>"
#define SENDTEXT(page, text) "<a href='" page ".html'>" text "</a>"

#define IMAGE(name) "<img src='../media/identity/" name "'/>"
#define PAR(content) "<p>" content "</p>"



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

Page* gates = create_page(art, "Gates");
add_preview_description(gates, "Third study on procedurally generated trees, going for a more abstract and twisted shapes.");

Page* scorci = create_page(art, "Scorci");
add_preview_description(scorci, "Second study on procedurally generated trees synthesising a Japanese panorama.");

Page* spring_flowers = create_page(art, "Spring Flowers");
add_preview_description(spring_flowers, "First study on procedurally generated trees.");
add_paragraph(spring_flowers, "It's Spring time! This is by far my favorite season of the year both for the warm clean air and for the beautiful show that trees create for us with their flowers. ");
add_paragraph(spring_flowers, "The idea for this series came by watching a tree right in front of my house. After few times passing beside it each day going to work, I thought that these branches and flowers could be recreated by some code and functions in Clojure.");
add_header(spring_flowers, "The style", 2);
add_paragraph(spring_flowers, "Once the idea was there, it was time to choose a way to represent that object into the canvas. This wasn't a hard choice to make, since as soon as I decided to try draw some trees, it instantly come to my mind the Japanese woodblock prints with their simplicity, style, and colors.");
add_header(spring_flowers, "The process", 2);
add_paragraph(spring_flowers, "This series started with some path studies. The path structure present inside generative-toolbelt was a nice start, but a simple disposed line wasn't good enough to emulate the flow and curves of the tree's branches. ");
add_image(spring_flowers, "default_1080.png");
add_paragraph(spring_flowers, "After some rework on the path generation, a decent twig-like path was ready to grow to a larger tree. The next thing was to make the branch split into smaller sub-branches in certain point of the path. After some troubles calculating the right angle to make the minor branches, the main branch generator function was ready to be reused many more times.");
add_image(spring_flowers, "default_1080.png");
add_image(spring_flowers, "default_1080.png");
add_image(spring_flowers, "default_1080.png");
add_paragraph(spring_flowers, "Once this was done, it was time for a lot of parameter tweaking. Often you can get a totally different look and feel from some piece of code by simply changing few arguments, if the code is well made and parametric.");
add_image(spring_flowers, "default_1080.png");
add_image(spring_flowers, "default_1080.png");
add_image(spring_flowers, "default_1080.png");
add_image(spring_flowers, "default_1080.png");
add_paragraph(spring_flowers, "Last but not least, the touch of spring. This will transform those spooky and naked branches into a well dressed and colorful tree. The flowers has been realized with a rose function with n=5 and d=2. I choose a regular function to give the flowers a \"mathematical\" touch that contrast well with the realistic randomness of the branches. ");
add_image(spring_flowers, "default_1080.png");
add_image(spring_flowers, "default_1080.png");
add_paragraph(spring_flowers, "With the flower in place, the base of the series generation was almost done. A few touches here and there to smooth out some rough edges and I was happy enough to create some high resolution images for the series. ");
add_header(spring_flowers, "There is more...", 2);
add_paragraph(spring_flowers, "I'm really happy with the result so far. I'm releasing this series as it is, but I feel that I can study this tree concept much more than this, so probably I'll keep working on this to expand and improve the style and composition of the artwork. So, if you liked this series, be sure to not miss the next one! ");



Page* deep_stars = create_page(art, "Deep Stars");
add_preview_description(deep_stars, "Studies on Quil blends and shapes.");

Page* color_mountains = create_page(art, "Color Mountains");
add_preview_description(color_mountains, "Part of my earliest studies on Quil blends.");


////////////////////////////
// Programs
////////////////////////////
Page* programs = create_page(home, "programs");

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
// About
////////////////////////////
Page* about = create_page(home, "about");
























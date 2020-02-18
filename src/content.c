
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



////////////////////////////
// Art
////////////////////////////
Page* art = create_page(home, "art");

Page* scorci = create_page(art, "Scorci");
add_preview_description(scorci, "Second study on procedurally generated trees synthesising a Japanese panorama.");

Page* spring_flowers = create_page(art, "Spring_Flowers");
add_preview_description(spring_flowers, "First study on procedurally generated trees.");

Page* gates = create_page(art, "Gates");
add_preview_description(gates, "Third study on procedurally generated trees, going for a more abstract and twisted shapes.");

Page* deep_stars = create_page(art, "Deep_Stars");
add_preview_description(deep_stars, "Studies on Quil blends and shapes.");

Page* color_mountains = create_page(art, "Color_Mountains");
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

create_page(home, "about");

























#define LINK(url)           "<a href='"url"' class='external' target='_blank'>"url"</a>"
#define LINKTEXT(url, name) "<a href='"url"' class='external' target='_blank'>"name"</a>"

#define SEND(page)           "<a href='" page ".html'>" page "</a>"
#define SENDTEXT(page, text) "<a href='" page ".html'>" text "</a>"

#define IMAGE(name) "<img src='../media/identity/" name "'/>"




Page* home = create_page(NULL, "home");
add_paragraph(home, "Welcome to ElKiwyArt website!");
add_paragraph(home, "This is my very personal attempt to show who am I, and what I do. Since I do many different things sprinkled around the internet, the scope of this website is trying to group them all up and present everything to you in a nice and simple way.");
add_paragraph(home, "This is not a simple portfolio where i present everything I made or released. There will also be random posts on anything I do in a particular time in my life, maybe some big project, or maybe just a little dumb study on something." );
add_paragraph(home, "");




create_page(home, "blog");
create_page(home, "art");

Page* programs = create_page(home, "programs");
create_page(programs, "Gisp");
create_page(programs, "PaYnter");

Page* games = create_page(home, "games");
create_page(games, "BeardedBear");
create_page(games, "BuildTutto");
create_page(games, "WaveJump");
create_page(games, "AsciiRush");

create_page(home, "about");


























WARNS = -Wpedantic -Wshadow -Wextra -Werror=implicit-int -Werror=incompatible-pointer-types -Werror=int-conversion
OPTIONS = -g -Og -fsanitize=address -fsanitize=undefined


main: main.c
	rm -f ../site/*
	rm -f ../media/thumb/*
	cc -std=c99 -DDEBUG $(WARNS) $(OPTIONS) -DCREATING_THUMBNAILS main.c -o main
	./main
	rm ./main


test: 
	rm -f ../site/*
	rm -f ../media/thumb/*
	cc -std=c99 -DDEBUG $(WARNS) $(OPTIONS) main.c -o main
	./main
	rm ./main


prod: 
	rm -f ../site/*
	rm -f ../media/thumb/*
	cc -std=c99 -DDEBUG $(WARNS) $(OPTIONS) -DCREATING_THUMBNAILS main.c -o main
	./main
	rm ./main










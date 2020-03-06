#!make
include .env
export $(shell sed 's/=.*//' .env)

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

env:
	echo $(FOO)

prod: 
	rm -f ../site/*
	rm -f ../media/thumb/*
	cc -std=c99 -DDEBUG $(WARNS) $(OPTIONS) -DCREATING_THUMBNAILS main.c -o main
	./main
	rm ./main

deploy:
	sftp $(FTP_USER)@$(FTP_HOST):$(FTP_ROOT) <<< $$'put -ar ../site\nput -ar ../links\nput -ar ../media'

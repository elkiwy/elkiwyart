#!make
include .env
export $(shell sed 's/=.*//' .env)

FLAGS = -DDEBUG -Wpedantic -Wshadow -Wextra -Werror=implicit-int -Werror=incompatible-pointer-types -Werror=int-conversion -g -Og -fsanitize=address -fsanitize=undefined -lm -ldl

main: main.c
	rm -f ../site/*
	rm -f ../media/thumb/*
	gcc -std=c99 $(FLAGS) -DCREATING_THUMBNAILS main.c -o main -lm -ldl
	./main
	rm ./main

test: 
	rm -f ../site/*
	rm -f ../media/thumb/*
	gcc -std=c99 $(FLAGS) main.c -o main -lm -ldl
	./main
	rm ./main

env:
	echo $(FOO)

prod: 
	rm -f ../site/*
	rm -f ../media/thumb/*
	gcc -std=c99 $(FLAGS) -DCREATING_THUMBNAILS main.c -o main -lm -ldl
	./main
	rm ./main

deploy:
	sftp $(FTP_USER)@$(FTP_HOST):$(FTP_ROOT) <<< $$'put -ar ../site\nput -ar ../links\nput -ar ../media'

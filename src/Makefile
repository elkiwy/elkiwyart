#!/bin/bash

SHELL := /bin/bash

include .env
export $(shell sed 's/=.*//' .env)


FLAGS = -DDEBUG -Wpedantic -Wshadow -Wextra -Werror=implicit-int -Werror=incompatible-pointer-types -Werror=int-conversion -g -Og -lm -ldl #-fsanitize=address -fsanitize=undefined 

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

deploy_preview:
	sftp $(FTP_USER)@$(FTP_HOST):$(FTP_ROOT_PREVIEW) <<< $$'put -r ../site\nput -r ../links\nput -r ../media'
deploy_prod:
	sftp $(FTP_USER)@$(FTP_HOST):$(FTP_ROOT_PROD) <<< $$'put -r ../site\nput -r ../links\nput -r ../media'

deploy_preview_content_only:
	sftp $(FTP_USER)@$(FTP_HOST):$(FTP_ROOT_PREVIEW) <<< $$'put -r ../site\nput -r ../links'
deploy_prod_content_only:
	sftp $(FTP_USER)@$(FTP_HOST):$(FTP_ROOT_PROD) <<< $$'put -r ../site\nput -r ../links'

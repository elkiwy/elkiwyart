#!/bin/bash

rm ../site/*
cc -std=c99 -DDEBUG -Wpedantic -Wshadow -Wextra -Werror=implicit-int -Werror=incompatible-pointer-types -Werror=int-conversion -g -Og -fsanitize=address -fsanitize=undefined main.c -o main
./main
rm ./main

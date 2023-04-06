CC = gcc
FLAGS = -Wall -Werror -Wextra

all: sborka go

sborka: game_of_life.c  
	$(CC) $(FLAGS)  game_of_life.c -o main

clang: 
	clang-format -i game_of_life.c

git: 
	git add . 
	git commit -m"make commit"
	git push origin main

go:
	./main
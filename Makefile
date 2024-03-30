FILELIST = \
main.c \
draw.h \
draw.c \
game.h \
game.c \

C_FLAGS = \
-ansi \
-g \

compile:
	mkdir -p output
	cc -o output/main $(FILELIST) -lncurses $(C_FLAGS)

clean:
	rm output/*

run: compile
	./output/main

leak-check: compile
	valgrind --leak-check=yes \
        --show-leak-kinds=all \
        --track-origins=yes \
		--show-reachable=no \
        --verbose \
		echo q > ./output/main

Filelist = \
main.c \
draw.h \
draw.c \
game.h \
game.c \

C_FLAGS = \
-ansi \
-g \

compile:
	cc -o main $(Filelist) -lncurses $(C_FLAGS)

clean:
	rm main

run: compile
	./main

debug:
	cc -o main main.c -lncurses -ansi -ggdb
	gdb ./main

leak-check: compile
	valgrind --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
		--show-reachable=no \
        --verbose \
        --log-file=valgrind-out.valgrind \
		./main

make:
	cc -o main main.c -lncurses -ansi

clean:
	rm main

run: make
	./main

debug:
	cc -o main main.c -lncurses -ansi -ggdb
	gdb ./main

leak-check: make
	valgrind --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        --log-file=valgrind-out.valgrind \
		./main
make:
	cc -o main main.c -lncurses -ansi

clean:
	rm main

run: make
	./main
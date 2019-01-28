all:	learn
learn:	learn.c
	gcc -g -Wall -Werror -fsanitize=address learn.c matrixops.c -o learn
clean:
	rm -rf learn
testCaseA: learn trainA.txt testA.txt
	./learn trainA.txt testA.txt

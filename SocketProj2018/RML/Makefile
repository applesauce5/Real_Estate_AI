all:	learn
learn:	learn.c
	gcc -g -Wall -Wextra -Werror -fsanitize=address learn.c matrixops.c -o learn
clean:
	rm -rf learn clean
testCaseA: learn trainA.txt testA.txt
	./learn trainA.txt testA.txt
.PHONY: all clean


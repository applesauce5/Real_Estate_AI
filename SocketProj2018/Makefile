all:	both
server:	server.c
	gcc -Wall -fsanitize=address server.c -g -o server
client:	client.c
	gcc -Wall -fsanitize=address client.c -g -o client
both:
	gcc -Wall -fsanitize=address server.c -g -o server
	gcc -Wall -fsanitize=address client.c -g -o client
testClient:
	gcc -Wall -fsanitize=address testClient.c -g -o testClient
testServer:
	gcc -Wall -fsanitize=address testServer.c ./RML/learn.c ./RML/matrixops.c -g -o testServer
test:
	gcc -Wall -o RML/learn.o RML/learn.c
	gcc -Wall -o SocketProj2018/testServer.o SocketProj2018/testServer.c
	gcc -Wall -fsanitize=address testServer.c -g -o testServer SocketProj2018/testServer.o RML/learn.o
	gcc -Wall -fsanitize=address testClient.c -g -o testClient
cleanTest:
	rm -rf testServer
	rm -rf testClient
clean: 
	rm -rf server
	rm -rf client

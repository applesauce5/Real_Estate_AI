all:	both
server:	server.c
	gcc -Wall -fsanitize=address server.c -g -o server
client:	client.c
	gcc -Wall -fsanitize=address client.c -g -o client
both:
	gcc -Wall -fsanitize=address server.c -g -o server
	gcc -Wall -fsanitize=address client.c -g -o client
test:
	gcc -Wall -fsanitize=address testServer.c -g -o testServer
	gcc -Wall -fsanitize=address testClient.c -g -o testClient
cleanTest:
	rm -rf testServer
	rm -rf testClient
clean: 
	rm -rf server
	rm -rf client

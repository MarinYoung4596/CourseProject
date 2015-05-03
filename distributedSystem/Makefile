all: file_server.o file_client.o
	gcc -o file_server file_server.o
	gcc -o file_client file_client.o

file_server.o:
	gcc -c file_server.c
file_client.o:
	gcc -c file_client.c

clean:
	rm -rf file_server file_client
	rm -rf *.o

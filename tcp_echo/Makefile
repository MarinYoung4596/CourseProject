# Makefile
# by MarinYoung
# 2013/12/15
all: server.o client.o
	gcc -o server server.o
	gcc -o client client.o

server.o: server.c unp.h sys.h
	gcc -c server.c
client.o: client.c unp.h sys.h
	gcc -c client.c
	
clean:
	rm -rf server client
	rm -rf *.o

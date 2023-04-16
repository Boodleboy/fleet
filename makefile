default: server client

codefiles = client.c\
			middleman.c\
			cons.c\
			hashmap.c

objfiles = client.o\
		   middleman.o\
		   cons.o\
		   hashmap.o

server: server.c
	gcc -o server server.c

client: client.c
	gcc -c $(codefiles)
	gcc -o client $(objfiles)

run:
	./server &
	./client

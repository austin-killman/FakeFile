CC = gcc

CFLAGS += -std=gnu11
CFLAGS += -Wall -Werror


defrag: main.c 
	${CC} ${CFLAGS} -pthread -o fake main.c -g
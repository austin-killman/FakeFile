CC = gcc

CFLAGS += -std=gnu11
CFLAGS += -Wall -Werror


defrag: fake.c 
	${CC} ${CFLAGS} -pthread -o fake fake.c -g
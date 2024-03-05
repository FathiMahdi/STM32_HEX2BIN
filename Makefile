SRC=main.c
COMPILER=gcc
FLAGS=-Wall
FLAGS+=-std=c11
OBJ=run


all:
	${COMPILER} ${SRC} -o ${OBJ} ${FLAGS}

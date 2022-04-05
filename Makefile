SRC = main.c
BIN ?= tty-battery 
LDFLAGS = -lncurses

tty-battery : ${SRC}
	@echo "building ${SRC}"
	gcc ${SRC} -o ${BIN} ${LDFLAGS}


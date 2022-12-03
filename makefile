SRC = $(wildcard src/*.c)

OBJS = $(patsubst src/%.c, bin/%.o, $(SRC))

.PHONY: all
all: bot_C

bot_C: bin/main.o bin/players.o
	gcc -o bot_C $(OBJS)

bin/main.o: src/main.c include/players.h bin
	gcc -c src/main.c -o bin/main.o 

bin/players.o: src/players.c include/players.h bin
	gcc -c src/players.c -o bin/players.o

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/*
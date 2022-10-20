
CC=clang

## Flags de compilation en mode debug, convient pour presque tout l'APP
CFLAGS= -g -Wall -Wextra -Werror -Wno-unused-parameter

objFiles = _build/main.o _build/curiosity.o _build/listes.o _build/interprete.o

all: curiosity-reloaded

_build/%.o: src/%.c
	$(CC) -c $< -o $@

curiosity-reloaded: $(objFiles)
	$(CC) $^ -o $@

clean:
	rm -f main *.o

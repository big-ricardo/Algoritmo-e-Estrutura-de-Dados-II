# Luis Ricardo

CC = gcc
CFLAGS = -pedantic-errors -Wall -g
LDFLASGS = -lm

FONTES = $(wildcard *.c)

OBJETOS = $(FONTES:.c=.o)

EXECUTAVEL = main.exe

all: $(EXECUTAVEL)

$(EXECUTAVEL) : $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLASGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o

run:
	./$(EXECUTAVEL)

rmproper: clean
	rm -rf $(EXECUTAVEL)

run: $(EXECUTAVEL)

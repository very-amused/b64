O=-O2
override CFLAGS += $(O) -march=native -Wall
ifndef CC
	CC=clang
endif
src=src/base64.c
objects=$(src:.c=.o)
base64=base64.a

$(base64): $(objects)
	ar rcs $@ $^

src/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

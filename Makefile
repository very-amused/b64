O=-O2
override CFLAGS += $(O) -march=native -Wall
ifndef CC
	CC=clang
endif
src=src/base64.c
objects=$(src:.c=.o)
lib=base64.a
main=base64

$(main): src/main.c $(lib)
	clang $(CFLAGS) -o $@ $^

$(lib): $(objects)
	ar rcs $@ $^

src/%.o: src/%.c
	clang $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(main) $(lib) $(objects)
.PHONY: clean

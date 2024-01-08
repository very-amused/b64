override CFLAGS += -O2 -Wall -I include/
src=src/base64.c
objects=$(src:.c=.o)
lib=b64.a
demo-src=src/demo.c
demo=b64_demo

$(lib): $(objects)
	$(AR) rcs $@ $^

demo: $(demo)
.PHONY: demo

$(demo): $(demo-src) $(lib)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(main) $(lib) $(objects)
.PHONY: clean

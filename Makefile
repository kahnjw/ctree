CFLAGS=-Wall -pedantic -Wextra

test: test/spec.c
	mkdir -p build
	$(CC) $(CFLAGS) -Iinclude -o build/spec test/spec.c
	build/spec

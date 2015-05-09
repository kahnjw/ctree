CFLAGS=-Wall -pedantic -Wextra -std=c99

testit: test/node_spec.c test/tree_spec.c
	mkdir -p build
	$(CC) $(CFLAGS) -Iinclude -o build/node_spec test/node_spec.c
	$(CC) $(CFLAGS) -Iinclude -o build/tree_spec test/tree_spec.c
	build/node_spec
	build/tree_spec

example: example/planets.c
	$(CC) $(CFLAGS) -Iinclude -o build/planets example/planets.c

analyze: example/planets.c
	$(CC) $(CFLAGS) -Iinclude -S -O2 -o build/planets.s example/planets.c


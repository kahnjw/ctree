CFLAGS=-Wall -pedantic -Wextra

testit: test/node_spec.c test/tree_spec.c
	mkdir -p build
	$(CC) $(CFLAGS) -Iinclude -o build/node_spec test/node_spec.c
	$(CC) $(CFLAGS) -Iinclude -o build/tree_spec test/tree_spec.c
	build/node_spec
	build/tree_spec

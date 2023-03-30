default: libdsa.so


libdsa.so: lib.c
	gcc -Werror -shared -O3 -fPIC -o libdsa.so lib.c

clean:
	rm -f libdsa.so p

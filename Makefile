
all: lib/static/libargparse.o lib/static/libargparse.a lib/shared/argparse.o lib/shared/libargparse.so #libargparse.so

lib/static/libargparse.o: argparse.c argparse.h
	mkdir -p lib/static
	gcc  -c $< -o $@

lib/static/libargparse.a: lib/static/libargparse.o
	mkdir -p lib/static
	ar rcs $@ $<

lib/shared/argparse.o: argparse.c argparse.h
	mkdir -p lib/shared
	gcc -c -fPIC $< -o $@

lib/shared/libargparse.so:  lib/shared/argparse.o
	mkdir -p lib/shared/
	gcc -shared $< -o $@

clean:
	rm -rf lib

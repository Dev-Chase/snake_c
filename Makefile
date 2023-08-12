#gcc -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a src/main.c -o bin/osx_build
CC = clang
CFLAGS = -g -Wall -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

build: obj/main.o obj/snake.o lib/libraylib.a
	$(CC) $(CFLAGS) $^ -o bin/osx_build

all: obj/main.o obj/snake.o build exec

run: build
	bin/osx_build

exec:
	bin/osx_build

# $< means first dependency
obj/%.o: src/%.c src/%.h src/settings.h
	gcc -c $< -o $@ 

obj/main.o: src/main.c src/settings.h
	gcc -c $< -o $@

clean:
	rm obj/snake.o obj/main.o bin/osx_build

C_FLAGS=-I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12
LIBS=-lcairo -lX11 -lXext -lXrender -lm

all: clean build

clean:
	rm -f balls

build:
	gcc balls.c -o balls ${C_FLAGS} ${LIBS}

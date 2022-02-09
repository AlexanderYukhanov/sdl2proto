CC = c++
INCLUDES = -I/usr/local/include
LIBINCLUDES = -L/usr/local/lib
INC = $(INCLUDES) $(LIBINCLUDES)
CFLAGS= -O2 -fPIC -Wall
LIBS=-lSDL2 -lSDL2_image

local: main.o
	$(CC) $(CFLAGS) $(LIBINCLUDES) main.o $(LIBS) -o local

main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c main.cpp

web:
	emcc -DEMS main.cpp -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file earth.png -s ALLOW_MEMORY_GROWTH=1 -o web.html

installlocal:
	sudo apt install git libsdl2-image-dev libsdl2-dev -y

installweb:
	git clone https://github.com/emscripten-core/emsdk.git
	sudo emsdk/emsdk install latest
	sudo emsdk/emsdk activate latest

runweb:
	python3 -m http.server

.PHONY: clean
clean:
	rm local *.o 2> /dev/null || true

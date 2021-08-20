local: main.cpp
	g++ main.cpp -lSDL2 -lSDL2_image -o local

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

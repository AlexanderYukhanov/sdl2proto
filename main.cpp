#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef EMS
#include <emscripten.h>
#endif

SDL_Window *window = nullptr;  
SDL_Renderer *renderer = nullptr;
SDL_Texture *texture = nullptr;

int x = 0;
int y = 0;
int w = 256;

bool game_loop(void *arg);
void draw();

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
  texture = IMG_LoadTexture(renderer, "image.png");
   
#ifndef EMS
  while(game_loop(nullptr)){
    SDL_Delay(1);
  }
#else
  emscripten_set_main_loop_arg(game_loop, nullptr, -1, true);
#endif
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool game_loop(void *) {
  SDL_Event event;
  int dx = 0;
  int dy = 0;
  while (SDL_PollEvent(&event)) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      dy = - 10;
      break;
    case SDLK_DOWN:
      dy = 10;
      break;
    case SDLK_LEFT:
      dx = -10;
      break;
    case SDLK_RIGHT:
      dx = 10;
      break;
    }
  }
  x += dx;
  y += dy;
  
  draw();
  SDL_RenderPresent(renderer);
  return event.type != SDL_QUIT;
}

void draw() {
  int width, height;
  SDL_GetWindowSize(window, &width, &height);
    
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
    
  SDL_SetRenderDrawColor(renderer, 127, 127, 127, 0);
  SDL_RenderDrawLine(renderer, 0, 0, width, height);
  SDL_RenderDrawLine(renderer, 0, height, width, 0);

  SDL_Rect rc {x, y, w, w};
  SDL_RenderCopy(renderer, texture, NULL, &rc);
}

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_version.h"
#include "SDL3/SDL_video.h"
#include <stdio.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  int sdl_version = SDL_GetVersion();
  printf("Using SDL v%d.%d.%d\n", SDL_VERSIONNUM_MAJOR(sdl_version),
         SDL_VERSIONNUM_MINOR(sdl_version), SDL_VERSIONNUM_MICRO(sdl_version));

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    dprintf(2, "Failed to initialize SDL: %s\n", SDL_GetError());
    return (1);
  }
  SDL_Window *window = SDL_CreateWindow("wordle gui", 1280, 720, 0);
  if (window == NULL) {
    dprintf(2, "Failed to create SDL window: %s\n", SDL_GetError());
    SDL_Quit();
    return (1);
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == NULL) {
    dprintf(2, "Failed to create SDL renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (1);
  }

  if (!SDL_StartTextInput(window)) {
    dprintf(2, "Failed to start SDL Text Input: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (1);
  }

  SDL_Event event;
  int running = 1;
  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        running = 0;
        break;
      case SDL_EVENT_TEXT_INPUT:
        printf("%s", event.text.text);
        fflush(stdout);
        break;
      case SDL_EVENT_KEY_DOWN:
        if (event.key.key == SDLK_RETURN)
          printf("\n");
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_StopTextInput(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return (0);
}

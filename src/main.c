#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_version.h"
#include "SDL3/SDL_video.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static SDL_Texture *load_bmp_texture(SDL_Renderer *renderer, char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);
  if (surface == NULL)
    return (NULL);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return (texture);
}

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

  char *rendererName = NULL;
  // NOTE: Keeping this for future debugging using renderdoc
  // printf("Available renderers: ");
  // int availableDrivers = SDL_GetNumRenderDrivers();
  // for (int i = 0; i < availableDrivers; i++) {
  //   const char *driver = SDL_GetRenderDriver(i);
  //   if (strstr(driver, "gles") != NULL) {
  //     rendererName = (char *)driver;
  //   }
  //   printf("%s%s", driver, (i == availableDrivers - 1 ? "" : " "));
  // }
  // printf("\nSelecting driver: %s\n", rendererName);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, rendererName);
  if (renderer == NULL) {
    dprintf(2, "Failed to create SDL renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (1);
  }
  if (!SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE)) {
    dprintf(2, "Failed to enable VSync: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (1);
  }

  SDL_Texture *charsTex = load_bmp_texture(renderer, "res/chars.bmp");
  if (charsTex == NULL) {
    dprintf(2, "Failed to load chars bitmap: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (1);
  }

  if (!SDL_StartTextInput(window)) {
    dprintf(2, "Failed to start SDL Text Input: %s\n", SDL_GetError());
    SDL_DestroyTexture(charsTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (1);
  }

  char guesses[6][6] = {0};
  int currentGuess = 0;

  SDL_Event event;
  int running = 1;
  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        running = 0;
        break;
      case SDL_EVENT_TEXT_INPUT:
        if (currentGuess >= 6)
          break;
        char chars[2] = {0};
        chars[0] = event.text.text[0];
        if (!isalpha(chars[0]))
          break;
        chars[0] = toupper(chars[0]);
        SDL_strlcat(guesses[currentGuess], chars, 6);
        break;
      case SDL_EVENT_KEY_DOWN:
        if (currentGuess >= 6)
          break;
        if (event.key.key == SDLK_RETURN)
          currentGuess++;
        if (event.key.key == SDLK_BACKSPACE) {
          int guessLen = strlen(guesses[currentGuess]);
          if (guessLen > 0) {
            guesses[currentGuess][guessLen - 1] = 0;
          }
        }
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < 6; i++) {
      char *guess = guesses[i];
      if (!*guess)
        break;
      for (int j = 0; j < 5; j++) {
        char c = guess[j];
        if (!c)
          break;
        SDL_FRect src = {.x = (c - 'A') * 64.f, .y = 0.f, .h = 64.f, .w = 64.f};
        SDL_FRect dst = {j * 64, i * 64, 64, 64};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderTexture(renderer, charsTex, &src, &dst);
      }
    }
    SDL_RenderPresent(renderer);
  }

  SDL_StopTextInput(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return (0);
}

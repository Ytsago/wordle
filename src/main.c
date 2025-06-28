#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_version.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "wordle.h"
#include "wordlegui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static SDL_Texture *load_bmp_texture(SDL_Renderer *renderer, char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);
  if (surface == NULL)
    return (NULL);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return (texture);
}

// TODO: better error handling, remove repetitions
int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  srand(time(NULL));
  if (argc != 2) {
    dprintf(2, "Usage: %s <words.txt>\n", argv[0]);
    return (1);
  }
  t_vector wordList;
  switch (parse_file(&wordList, argv[1])) {
  case -1:
    dprintf(2, "Failed to load words: system error\n");
    break;
  case -2:
    dprintf(2, "Failed to load words: invalid file format\n");
    break;
  case -3:
    dprintf(2, "Failed to load words: not enough words\n");
    break;
  }

  int sdl_version = SDL_GetVersion();
  printf("Using SDL v%d.%d.%d\n", SDL_VERSIONNUM_MAJOR(sdl_version),
         SDL_VERSIONNUM_MINOR(sdl_version), SDL_VERSIONNUM_MICRO(sdl_version));

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    dprintf(2, "Failed to initialize SDL: %s\n", SDL_GetError());
    free_dic(&wordList);
    return (1);
  }
  if (!TTF_Init()) {
    dprintf(2, "Failed to initialize SDL ttf: %s\n", SDL_GetError());
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }
  SDL_Window *window = SDL_CreateWindow("wordle gui", 1280, 720, 0);
  if (window == NULL) {
    dprintf(2, "Failed to create SDL window: %s\n", SDL_GetError());
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
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
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }
  if (!SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE)) {
    dprintf(2, "Failed to enable VSync: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }

  SDL_Texture *charsTex = load_bmp_texture(renderer, "res/chars.bmp");
  if (charsTex == NULL) {
    dprintf(2, "Failed to load chars bitmap: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }

  TTF_Font *font = TTF_OpenFont("res/Ubuntu-Regular.ttf", 24);
  if (font == NULL) {
    dprintf(2, "Failed to load ttf font: %s\n", SDL_GetError());
    SDL_DestroyTexture(charsTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }

  if (!SDL_StartTextInput(window)) {
    dprintf(2, "Failed to start SDL Text Input: %s\n", SDL_GetError());
    TTF_CloseFont(font);
    SDL_DestroyTexture(charsTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }

  SDL_Texture *textTex = NULL;
  SDL_Surface *textSurface = TTF_RenderText_Blended(
      font, "Hello, world!", 0, (SDL_Color){255, 255, 255, 255});
  if (textSurface) {
    textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
  }
  if (textTex == NULL) {
    dprintf(2, "Failed to start SDL Text Input: %s\n", SDL_GetError());
    SDL_StopTextInput(window);
    TTF_CloseFont(font);
    SDL_DestroyTexture(charsTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    free_dic(&wordList);
    return (1);
  }

  char *word = get_random_word(&wordList);
  Gui gui = {{window, renderer, charsTex, textTex, font, 1},
             {&wordList, word, {0}, 0}};
  while (gui.sdl.loopRunning) {
    wordle_logic(&gui);
    render_wordle(&gui);
  }

  SDL_StopTextInput(window);
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  free_dic(&wordList);
  return (0);
}

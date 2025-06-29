#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_error.h"
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

#define GUIASSERTERROR(gui, expr, str)                                         \
  if (expr) {                                                                  \
    dprintf(2, "%s: %s\n", str, SDL_GetError());                               \
    free_gui(&gui);                                                            \
    return (1);                                                                \
  };

static SDL_Texture *load_bmp_texture(SDL_Renderer *renderer, char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);
  if (surface == NULL)
    return (NULL);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return (texture);
}

static SDL_Texture *render_text(SDL_Renderer *renderer, TTF_Font *font,
                                const char *text) {
  SDL_Surface *surface =
      TTF_RenderText_Blended(font, text, 0, (SDL_Color){255, 255, 255, 255});
  if (surface == NULL)
    return (NULL);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return (texture);
}

static void free_gui(Gui *gui) {
  if (gui->sdl.window && SDL_TextInputActive(gui->sdl.window))
    SDL_StopTextInput(gui->sdl.window);
  if (gui->sdl.playAgainLabel)
    SDL_DestroyTexture(gui->sdl.playAgainLabel);
  if (gui->sdl.referenceLabel)
    SDL_DestroyTexture(gui->sdl.referenceLabel);
  if (gui->sdl.font)
    TTF_CloseFont(gui->sdl.font);
  if (gui->sdl.charsTex)
    SDL_DestroyTexture(gui->sdl.charsTex);
  if (gui->sdl.renderer)
    SDL_DestroyRenderer(gui->sdl.renderer);
  if (gui->sdl.window)
    SDL_DestroyWindow(gui->sdl.window);
  if (gui->game.wordList)
    free_dic(gui->game.wordList);
  if (TTF_WasInit())
    TTF_Quit();
  if (SDL_WasInit(SDL_INIT_VIDEO))
    SDL_Quit();
}

// TODO: better error handling, remove repetitions
int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  srand(time(NULL) / 86400);
  if (argc != 2) {
    dprintf(2, "Usage: %s <words.txt>\n", argv[0]);
    return (1);
  }

  Gui gui = {0};

  t_vector wordList;
  switch (parse_file(&wordList, argv[1])) {
  case -1:
    dprintf(2, "Failed to load words: system error\n");
    return (1);
  case -2:
    dprintf(2, "Failed to load words: invalid file format\n");
    return (1);
  case -3:
    dprintf(2, "Failed to load words: not enough words\n");
    return (1);
  }
  gui.game.wordList = &wordList;

  int sdl_version = SDL_GetVersion();
  printf("Using SDL v%d.%d.%d\n", SDL_VERSIONNUM_MAJOR(sdl_version),
         SDL_VERSIONNUM_MINOR(sdl_version), SDL_VERSIONNUM_MICRO(sdl_version));

  GUIASSERTERROR(gui, !SDL_Init(SDL_INIT_VIDEO), "Failed to initialize SDL");
  GUIASSERTERROR(gui, !TTF_Init(), "Failed to initialize SDL ttf");
  gui.sdl.window = SDL_CreateWindow("wordle gui", 780, 550, 0);
  GUIASSERTERROR(gui, gui.sdl.window == NULL, "Failed to create SDL window");

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

  gui.sdl.renderer = SDL_CreateRenderer(gui.sdl.window, rendererName);
  GUIASSERTERROR(gui, gui.sdl.renderer == NULL,
                 "Failed to create SDL renderer");
  GUIASSERTERROR(
      gui, !SDL_SetRenderVSync(gui.sdl.renderer, SDL_RENDERER_VSYNC_ADAPTIVE),
      "Failed to enable VSync");
  GUIASSERTERROR(
      gui, !SDL_SetRenderDrawBlendMode(gui.sdl.renderer, SDL_BLENDMODE_BLEND),
      "Failed to set render blend mode");

  gui.sdl.charsTex = load_bmp_texture(gui.sdl.renderer, "res/chars.bmp");
  GUIASSERTERROR(gui, gui.sdl.charsTex == NULL, "Failed to load chars bitmap");

  gui.sdl.font = TTF_OpenFont("res/Ubuntu-Regular.ttf", 24);
  GUIASSERTERROR(gui, gui.sdl.font == NULL, "Failed to load ttf font");

  gui.sdl.referenceLabel =
      render_text(gui.sdl.renderer, gui.sdl.font, "Reference");
  GUIASSERTERROR(gui, gui.sdl.referenceLabel == NULL,
                 "Failed to pre-render reference label");

  gui.sdl.playAgainLabel =
      render_text(gui.sdl.renderer, gui.sdl.font, "Press ENTER to play again");
  GUIASSERTERROR(gui, gui.sdl.playAgainLabel == NULL,
                 "Failed to pre-render play again text");

  GUIASSERTERROR(gui, !SDL_StartTextInput(gui.sdl.window),
                 "Failed to start SDL Text Input");

  gui.game.word = get_random_word(&wordList);
  gui.sdl.loopRunning = 1;
  while (gui.sdl.loopRunning) {
    GUIASSERTERROR(gui, !wordle_logic(&gui), "Error during game loop");
    render_wordle(&gui);
  }

  free_gui(&gui);
  return (0);
}

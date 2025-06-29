#ifndef WORDLEGUI_H
#define WORDLEGUI_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "libft.h"

typedef struct SDLContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *charsTex;
  SDL_Texture *textStatus;
  SDL_Texture *referenceLabel;
  TTF_Font *font;
  int loopRunning;
} SDLContext;

typedef struct Guess {
  char guess[6];
  int state[5];
} Guess;

typedef struct GameState {
  t_vector *wordList;
  char *word;
  Guess guesses[6];
  int currentGuess;
  char reference[26];
} GameState;

typedef struct Gui {
  SDLContext sdl;
  GameState game;
} Gui;

int wordle_logic(Gui *gui);
void render_wordle(Gui *gui);

#endif // WORDLEGUI_H

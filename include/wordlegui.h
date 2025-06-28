#ifndef WORDLEGUI_H
#define WORDLEGUI_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

typedef struct SDLContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *charsTex;
  int loopRunning;
} SDLContext;

typedef struct Guess {
  char guess[6];
  int state[5];
} Guess;

typedef struct GameState {
  Guess guesses[6];
  int currentGuess;
} GameState;

typedef struct Gui {
  SDLContext sdl;
  GameState game;
} Gui;

void wordle_logic(Gui *gui);
void render_wordle(Gui *gui);

#endif // WORDLEGUI_H

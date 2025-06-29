#ifndef WORDLEGUI_H
#define WORDLEGUI_H

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "libft.h"

#define CONFETTI_AMOUNT 1024

typedef struct SDLContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *charsTex;
  SDL_Texture *textStatus;
  SDL_Texture *referenceLabel;
  SDL_Texture *playAgainLabel;
  SDL_Texture *confetti;
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
  int end;
} GameState;

typedef struct Confetti {
  float x;
  float y;
  float vx;
  float vy;
  float drag;
  float gravity;
  float angle;
  float angularVelocity;
  float angularDrag;
  int textureIndex;
} Confetti;

typedef struct WinAnimation {
  int started;
  int finished;
  Confetti *confetti;
  int confettiAmount;
} WinAnimation;

typedef struct Gui {
  SDLContext sdl;
  GameState game;
  WinAnimation win;
} Gui;

int wordle_logic(Gui *gui);
void render_wordle(Gui *gui);
void render_confetti(Gui *gui);

#endif // WORDLEGUI_H

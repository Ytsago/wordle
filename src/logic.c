#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "wordle.h"
#include "wordlegui.h"
#include <ctype.h>
#include <string.h>

static int build_text(Gui *gui, const char *str) {
  if (gui->sdl.textStatus) {
    SDL_DestroyTexture(gui->sdl.textStatus);
    gui->sdl.textStatus = NULL;
  }
  SDL_Surface *surf = TTF_RenderText_Blended(gui->sdl.font, str, 0,
                                             (SDL_Color){255, 255, 255, 255});
  if (surf) {
    gui->sdl.textStatus = SDL_CreateTextureFromSurface(gui->sdl.renderer, surf);
    SDL_DestroySurface(surf);
  }
  if (gui->sdl.textStatus == NULL)
    return (-1);
  return (0);
}

static int test_word(Gui *gui) {
  Guess *guess = &gui->game.guesses[gui->game.currentGuess];
  if (strlen(guess->guess) != 5)
    return (build_text(gui, "Not a 5 letter word"));
  if (!is_in_word_list(gui->game.wordList, guess->guess))
    return (build_text(gui, "Unrecognized word"));

  get_feedback(guess->guess, gui->game.word, guess->state);
  gui->game.currentGuess++;
  int *s = guess->state;
  if (s[0] == 2 && s[1] == 2 && s[2] == 2 && s[3] == 2 && s[4] == 2) {
    SDL_StopTextInput(gui->sdl.window);
    return (build_text(gui, "Congratulation!!") | 1);
  }
  if (gui->game.currentGuess == 6) {
    char gameover[64] = {0};
    SDL_strlcat(gameover, "Game Over! The word was ", 64);
    SDL_strlcat(gameover, gui->game.word, 64);
    SDL_StopTextInput(gui->sdl.window);
    return (build_text(gui, gameover) | 1);
  }
  return (1);
}

static void clear_state(Gui *gui) {
  Guess *guess = &gui->game.guesses[gui->game.currentGuess];
  memset(guess->state, 0, sizeof(int) * 5);
  SDL_DestroyTexture(gui->sdl.textStatus);
  gui->sdl.textStatus = NULL;
}

int wordle_logic(Gui *gui) {
  SDL_Event event;
  Guess *guess = &gui->game.guesses[gui->game.currentGuess];

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      gui->sdl.loopRunning = 0;
      break;

    case SDL_EVENT_TEXT_INPUT:
      if (gui->game.currentGuess >= 6 || strlen(guess->guess) >= 5)
        break;
      char chars[2] = {0};
      chars[0] = event.text.text[0];
      if (!isalpha(chars[0]))
        break;
      chars[0] = tolower(chars[0]);
      SDL_strlcat(guess->guess, chars, 6);
      clear_state(gui);
      break;

    case SDL_EVENT_KEY_DOWN:
      if (gui->game.currentGuess >= 6)
        break;
      if (event.key.key == SDLK_RETURN) {
        switch (test_word(gui)) {
        case 0:
          for (unsigned long i = 0; i < strlen(guess->guess); i++)
            guess->state[i] = 3;
          break;
        case -1:
          return (0);
        }
      }
      if (event.key.key == SDLK_BACKSPACE) {
        int guessLen = strlen(guess->guess);
        if (guessLen > 0) {
          guess->guess[guessLen - 1] = 0;
        }
        clear_state(gui);
      }
      break;
    }
  }

  return (1);
}

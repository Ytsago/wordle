#include "SDL3/SDL_stdinc.h"
#include "wordlegui.h"
#include <ctype.h>

static void test_word(Gui *gui) { gui->game.currentGuess++; }

void wordle_logic(Gui *gui) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      gui->sdl.loopRunning = 0;
      break;
    case SDL_EVENT_TEXT_INPUT:
      if (gui->game.currentGuess >= 6)
        break;
      char chars[2] = {0};
      chars[0] = event.text.text[0];
      if (!isalpha(chars[0]))
        break;
      chars[0] = toupper(chars[0]);
      SDL_strlcat(gui->game.guesses[gui->game.currentGuess].guess, chars, 6);
      break;
    case SDL_EVENT_KEY_DOWN:
      if (gui->game.currentGuess >= 6)
        break;
      Guess *guess = &gui->game.guesses[gui->game.currentGuess];
      if (event.key.key == SDLK_RETURN)
        test_word(gui);
      if (event.key.key == SDLK_BACKSPACE) {
        int guessLen = strlen(guess->guess);
        if (guessLen > 0) {
          guess->guess[guessLen - 1] = 0;
        }
      }
      break;
    }
  }
}

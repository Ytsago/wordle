#include "SDL3/SDL_stdinc.h"
#include "wordle.h"
#include "wordlegui.h"
#include <ctype.h>
#include <string.h>

static int test_word(t_vector *list, Guess *guess, char *word) {
  if (strlen(guess->guess) != 5)
    return (0);
  if (!is_in_word_list(list, guess->guess))
    return (0);

  // FIXME: This'll break in the future
  get_feedback(guess->guess, word, guess->state);
  return (1);
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
      memset(guess->state, 0, sizeof(int) * 5);
      break;
    case SDL_EVENT_KEY_DOWN:
      if (gui->game.currentGuess >= 6)
        break;
      if (event.key.key == SDLK_RETURN) {
        if (test_word(gui->game.wordList, guess, gui->game.word))
          gui->game.currentGuess++;
        else {
          for (unsigned long i = 0; i < strlen(guess->guess); i++)
            guess->state[i] = 3;
        }
      }
      if (event.key.key == SDLK_BACKSPACE) {
        int guessLen = strlen(guess->guess);
        if (guessLen > 0) {
          guess->guess[guessLen - 1] = 0;
        }
        memset(guess->state, 0, sizeof(int) * 5);
      }
      break;
    }
  }
  return (0);
}

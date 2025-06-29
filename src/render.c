#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "wordlegui.h"

void render_wordle(Gui *gui) {
  const float start_x = 25.f;
  const float start_y = 25.f;
  const float offset_x = 5.f;
  const float offset_y = 10.f;
  const float square_size = 64.f;
  const float middle_x = start_x + offset_x * 2.f + square_size * 2.5f;
  const float reference_start_x =
      start_x * 2.f + offset_x * 4.f + square_size * 5.f;
  const float reference_label_y = 15.f;
  const float reference_start_y = 50.f;

  const int bg_col[3] = {35, 35, 35};
  const int yellow_col[3] = {232, 213, 65};
  const int green_col[3] = {53, 204, 86};
  const int red_col[3] = {230, 55, 55};

  SDL_SetRenderDrawColor(gui->sdl.renderer, bg_col[0], bg_col[1], bg_col[2],
                         255);
  SDL_RenderClear(gui->sdl.renderer);

  for (int gi = 0; gi < 6; gi++) {
    Guess *guess = &gui->game.guesses[gi];
    for (int ci = 0; ci < 5; ci++) {
      char c = guess->guess[ci];
      SDL_FRect dst = {
          .x = start_x + ci * square_size + offset_x * ci,
          .y = start_y + gi * square_size + offset_y * gi,
          .w = square_size,
          .h = square_size,
      };
      {
        const int *draw_col;
        switch (guess->state[ci]) {
        case 0:
          draw_col = bg_col;
          break;
        case 1:
          draw_col = yellow_col;
          break;
        case 2:
          draw_col = green_col;
          break;
        default:
          draw_col = red_col;
          break;
        }
        SDL_SetRenderDrawColor(gui->sdl.renderer, draw_col[0], draw_col[1],
                               draw_col[2], 255);
      }
      SDL_RenderFillRect(gui->sdl.renderer, &dst);
      if (gi <= gui->game.currentGuess)
        SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
      else
        SDL_SetRenderDrawColor(gui->sdl.renderer, 100, 100, 100, 255);
      SDL_RenderRect(gui->sdl.renderer, &dst);
      SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
      if (c) {
        SDL_FRect src = {
            .x = (c - 'a') * square_size,
            .y = 0.f,
            .w = square_size,
            .h = square_size,
        };
        SDL_RenderTexture(gui->sdl.renderer, gui->sdl.charsTex, &src, &dst);
      }
    }
  }
  if (gui->sdl.textStatus) {
    SDL_FRect dst = {
        .x = middle_x - gui->sdl.textStatus->w * 0.5f,
        .y = start_y + offset_y * 7.f + square_size * 6.f,
        .w = gui->sdl.textStatus->w,
        .h = gui->sdl.textStatus->h,
    };
    SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
    SDL_RenderTexture(gui->sdl.renderer, gui->sdl.textStatus, NULL, &dst);
  }
  {
    SDL_SetRenderDrawColor(gui->sdl.renderer, 100, 100, 100, 255);
    SDL_RenderLine(gui->sdl.renderer, reference_start_x, 0.f, reference_start_x,
                   550.f);
  }
  {
    SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
    SDL_FRect dst = {
        .x = reference_start_x + start_x,
        .y = reference_label_y,
        .w = gui->sdl.referenceLabel->w,
        .h = gui->sdl.referenceLabel->h,
    };
    SDL_RenderTexture(gui->sdl.renderer, gui->sdl.referenceLabel, NULL, &dst);
    for (int i = 0; i < 6; i++) {
      SDL_FRect dst = {
          .x = reference_start_x + start_x,
          .y = reference_start_y + 64.f * i,
          .w = i == 5 ? 64.f : 320.f,
          .h = 64.f,
      };
      SDL_FRect src = {
          .x = i * 320.f,
          .y = 0.f,
          .w = i == 5 ? 64.f : 320.f,
          .h = 64.f,
      };
      SDL_RenderTexture(gui->sdl.renderer, gui->sdl.charsTex, &src, &dst);
    }
    for (int i = 0; i < 26; i++) {
      char ref = gui->game.reference[i];
      if (!ref)
        continue;
      SDL_FRect dst = {
          .x = reference_start_x + start_x + 64.f * (i % 5),
          .y = reference_start_y + 64.f * (int)(i / 5),
          .w = 64.f,
          .h = 64.f,
      };
      if (ref == 1) {
        // TODO: put crosses
        // SDL_RenderTexture(gui->sdl.renderer, gui->sdl.cross, NULL, &dst);
        SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 0, 0, 100);
        SDL_RenderFillRect(gui->sdl.renderer, &dst);
      } else if (ref == 2) {
        SDL_SetRenderDrawColor(gui->sdl.renderer, 0, 255, 0, 100);
        SDL_RenderFillRect(gui->sdl.renderer, &dst);
      }
    }
  }
  SDL_RenderPresent(gui->sdl.renderer);
}

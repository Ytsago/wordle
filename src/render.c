#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "wordlegui.h"

void render_wordle(Gui *gui) {
  const float start_x = 25.f;
  const float start_y = 25.f;
  const float offset_x = 5.f;
  const float offset_y = 10.f;

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
          .x = start_x + ci * 64 + offset_x * ci,
          .y = start_y + gi * 64 + offset_y * gi,
          .w = 64,
          .h = 64,
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
      SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
      SDL_RenderRect(gui->sdl.renderer, &dst);
      if (c) {
        SDL_FRect src = {
            .x = (c - 'a') * 64.f,
            .y = 0.f,
            .w = 64.f,
            .h = 64.f,
        };
        SDL_RenderTexture(gui->sdl.renderer, gui->sdl.charsTex, &src, &dst);
      }
    }
  }
  if (gui->sdl.textStatus) {
    SDL_FRect dst = {
        .x = 10.f,
        .y = start_y + offset_y * 7.f + 64.f * 6.f,
        .w = gui->sdl.textStatus->w,
        .h = gui->sdl.textStatus->h,
    };
    SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
    SDL_RenderTexture(gui->sdl.renderer, gui->sdl.textStatus, NULL, &dst);
  }
  SDL_RenderPresent(gui->sdl.renderer);
}

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "wordlegui.h"
#include <math.h>
#include <stdlib.h>

static float random_float(float a) {
  return ((float)rand() / (float)(RAND_MAX / a));
}

static void init_confetti(WinAnimation *win, int textureCount) {
  const double pi =
      3.1415926535897932384626433832795028841971693993751058209749445923078164;
  const double pi_2 = pi / 2.;
  const double pi_4 = pi / 4.;
  const double pi_6 = pi / 6.;
  const double pi_5_6 = pi - pi_6;

  for (int i = 0; i < win->confettiAmount; i++) {
    Confetti *cft = &win->confetti[i];
    double angleDir = (i % 2) ? pi_6 : pi_5_6;
    double angleDirVar = random_float(pi_2) - pi_4;
    float xdir = cos(angleDir + angleDirVar);
    float ydir = sin(angleDir + angleDirVar);
    float velocity = random_float(20.f) + 5.f;
    cft->x = (i % 2) ? -17.f : 797.f;
    cft->y = 550.f;
    cft->vx = xdir * velocity;
    cft->vy = -ydir * velocity;
    cft->gravity = random_float(0.2f) + 0.2f;
    cft->drag = random_float(0.01f) + 1.02f;
    cft->angle = random_float(360.f);
    cft->angularVelocity = random_float(10.f) - 5.f;
    cft->angularDrag = random_float(0.1f) + 1.05f;
    cft->textureIndex = rand() % textureCount;
  }
  win->started = 1;
}

void render_confetti(Gui *gui) {
  const float confetti_square = 16.f;

  WinAnimation *win = &gui->win;
  if (!win->started)
    init_confetti(win, gui->sdl.confetti->w / gui->sdl.confetti->h);
  if (win->finished)
    return;

  int all_offscreen = 1;
  SDL_SetRenderDrawColor(gui->sdl.renderer, 255, 255, 255, 255);
  for (int i = 0; i < gui->win.confettiAmount; i++) {
    Confetti *cft = &win->confetti[i];
    cft->vy += cft->gravity;
    cft->vx /= cft->drag;
    cft->angularVelocity /= cft->angularDrag;
    cft->x += cft->vx;
    cft->y += cft->vy;
    cft->angle += cft->angularVelocity;
    if (cft->y > (550.f + confetti_square))
      continue;
    all_offscreen = 0;
    SDL_FRect dst = {
        .x = cft->x - confetti_square / 2.f,
        .y = cft->y - confetti_square / 2.f,
        .w = confetti_square,
        .h = confetti_square,
    };
    SDL_FRect src = {
        .x = cft->textureIndex * confetti_square,
        .y = 0.f,
        .w = confetti_square,
        .h = confetti_square,
    };
    SDL_RenderTextureRotated(gui->sdl.renderer, gui->sdl.confetti, &src, &dst,
                             cft->angle, NULL, 0);
  }
  if (all_offscreen)
    win->finished = 1;
}

#include <raylib.h>
#include <stdlib.h>
#include "noise.h"

#define SCR_WIDTH  960
#define SCR_HEIGHT 720
#define PX         8
#define TARGET_FPS 14
#define TITLE      "perlin noise"

#define COLOR_BG GetColor(0x181818FF)

int main(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCR_WIDTH, SCR_HEIGHT, TITLE);
  SetTargetFPS(TARGET_FPS);

  while (!WindowShouldClose()) {
    Texture2D tex_ns_perlin = tex_gen_noise_perlin(SCR_WIDTH, SCR_HEIGHT, PX,
                                                   2402,
                                                   /* GetRandomValue(100, 3000), */
                                                   fd_linear);
    /* Texture2D tex_ns_perlin = tex_gen_noise_white(SCR_WIDTH, SCR_HEIGHT, PX); */
    BeginDrawing();
      ClearBackground(COLOR_BG);
      DrawTexture(tex_ns_perlin, 0, 0, WHITE);
    EndDrawing();
    UnloadTexture(tex_ns_perlin);
  }

  CloseWindow();
  exit(EXIT_SUCCESS);
}

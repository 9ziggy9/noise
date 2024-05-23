#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#define SCR_WIDTH  960
#define SCR_HEIGHT 720
#define PX         8
#define TARGET_FPS 144
#define TITLE      "perlin noise"

#define COLOR_BG GetColor(0x181818FF)

Texture2D tex_gen_rand_map(int, int, int);
Texture2D tex_gen_noise_white(int, int, int);
Texture2D tex_gen_noise_perlin(int, int, int);

int main(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCR_WIDTH, SCR_HEIGHT, TITLE);
  SetTargetFPS(TARGET_FPS);

  while (!WindowShouldClose()) {
    Texture2D tex_ns_perlin = tex_gen_noise_perlin(SCR_WIDTH, SCR_HEIGHT, PX);
    BeginDrawing();
      ClearBackground(COLOR_BG);
      DrawTexture(tex_ns_perlin, 0, 0, WHITE);
    EndDrawing();
    UnloadTexture(tex_ns_perlin);
  }

  CloseWindow();
  exit(EXIT_SUCCESS);
}

Texture2D tex_gen_rand_map(int w, int h, int px) {
  Image img = GenImageColor(w, h, BLANK);
  for (int y = 0; y < h; y += px) {
    for (int x = 0; x < w; x += px) {
      Color color = (Color) {
        .r = (unsigned char) GetRandomValue(0, 255),
        .g = (unsigned char) GetRandomValue(0, 255),
        .b = (unsigned char) GetRandomValue(0, 255),
        .a = 255
      };
      ImageDrawRectangle(&img, x, y, px, px, color);
    }
  }
  return LoadTextureFromImage(img);
}

Texture2D tex_gen_noise_white(int w, int h, int px) {
  Image img = GenImageColor(w, h, BLANK);
  for (int y = 0; y < h; y += px) {
    for (int x = 0; x < w; x += px) {
      float noise = (float) GetRandomValue(0, 255) / 255.0f;
      Color color = (Color) {
        .r = 0,
        .g = (unsigned char) (noise * 255),
        .b = 0,
        .a = 255
      };
      ImageDrawRectangle(&img, x, y, px, px, color);
    }
  }
  return LoadTextureFromImage(img);
}

// BEGIN: PERLIN
static inline float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
static inline float lerp(float t, float a, float b) { return a + t * (b - a); }
static float grad(int hash, float x, float y) {
  int h = hash % 4;
  float u, v;
  switch (h) {
    case 0:  u =  x; v =  y; break;
    case 1:  u = -x; v =  y; break;
    case 2:  u =  x; v = -y; break;
    default: u = -x; v = -y; break;
  }
  return u + v;
}

float perlin_noise(float x, float y, int seed) {
  int x0 = (int) floorf(x);
  int x1 = x0 + 1;
  int y0 = (int) floorf(y);
  int y1 = y0 + 1;

  float sx = x - (float) x0;
  float sy = y - (float) y0;

  int hash00 = (x0 + y0 * 57 + seed) % 100;
  int hash01 = (x0 + y1 * 57 + seed) % 100;
  int hash10 = (x1 + y0 * 57 + seed) % 100;
  int hash11 = (x1 + y1 * 57 + seed) % 100;

  float n0 = grad(hash00, sx,     sy);
  float n1 = grad(hash10, sx - 1, sy);
  float n2 = grad(hash01, sx,     sy - 1);
  float n3 = grad(hash11, sx - 1, sy - 1);

  float n_x0y0 = lerp(fade(sx), n0, n1);
  float n_x1y0 = lerp(fade(sx), n2, n3);

  return lerp(fade(sy), n_x0y0, n_x1y0);
}

Texture2D tex_gen_noise_perlin(int w, int h, int px) {
  Image img = GenImageColor(w, h, BLANK);
  float scale = 10.0f;
  for (int y = 0; y < h; y += px) {
    for (int x = 0; x < w; x += px) {
      float noise = perlin_noise((float) x / px / scale,
                                 (float) y / px / scale, 1984);
      noise = (noise + 1.0f) / 2.0f;
      Color color = (Color) {
        .r = 0,
        .g = (unsigned char) (noise * 255),
        .b = 0,
        .a = 255
      };
      ImageDrawRectangle(&img, x, y, px, px, color);
    }
  }
  return LoadTextureFromImage(img);
}
// END: PERLIN

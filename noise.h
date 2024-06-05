#ifndef NOISE_H_
#define NOISE_H_
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

typedef float (*fade_fn)(float);
typedef float (*perlin_fn)(float, float);

struct perlin_spec {
  int seed;
  fade_fn fn;
  size_t octaves;
  float lacunarity;
  float persistance;
};

static inline float lerp(float t, float a, float b) { return a + t * (b - a); }
static inline float fd_perlin(float t) {
  return t * t * t * (t * (t * 6 - 15) + 10);
}
static inline float fd_linear(float t) { return t; }
static inline int hash(int x, int y, int seed) {
  srand(x + y * 57 + seed);
  return rand() % 100;
}

float perlin_compose(float x, float y, struct perlin_spec spec);

Texture2D tex_gen_noise_perlin(int, int, int, int, fade_fn);

#endif // NOISE_H_

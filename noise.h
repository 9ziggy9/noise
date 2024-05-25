#ifndef NOISE_H_
#define NOISE_H_
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

typedef float (*fade_fn)(float);

static inline float lerp(float t, float a, float b) { return a + t * (b - a); }
static inline float fd_perlin(float t) {
/* NOTES:
   Note that the "fade" function utilizes a polynomial curve whose derivatives
   (first and second) vanish at the boundaries. Perlin's original implementation
   in fact used a cubic Hermite spline (Hermite blending function 3t^2 - 2t^3):
   https://en.wikipedia.org/wiki/Cubic_Hermite_spline */
  return t * t * t * (t * (t * 6 - 15) + 10);
}
static inline float fd_linear(float t) { return t; }
static inline int hash(int x, int y, int seed) {
  srand(x + y * 57 + seed);
  return rand() % 100;
}

Texture2D tex_gen_rand_map(int, int, int);
Texture2D tex_gen_noise_white(int, int, int);
Texture2D tex_gen_noise_perlin(int, int, int, int, fade_fn);

#endif // NOISE_H_

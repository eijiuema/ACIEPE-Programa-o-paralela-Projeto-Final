#include <stdio.h>
#include <time.h>

#include "lib\simplexnoise.h"

#define WIDTH 4096
#define HEIGHT 4096
#define NUM_TESTS 10

enum Biome { WATER, BEACH, FOREST, JUNGLE, SAVANNAH, DESERT, SNOW };

float noise(float x, float y) { return raw_noise_2d(x, y) / 2.0 + 0.5; }

Biome biome(float e) {
    if (e < 0.1)
        return WATER;
    else if (e < 0.2)
        return BEACH;
    else if (e < 0.3)
        return FOREST;
    else if (e < 0.5)
        return JUNGLE;
    else if (e < 0.7)
        return SAVANNAH;
    else if (e < 0.9)
        return DESERT;
    else
        return SNOW;
}

int main() {
    Biome* map_biome = new Biome[WIDTH * HEIGHT];
    float* map_elevation = new float[WIDTH * HEIGHT];
    for (int i = 0; i < NUM_TESTS; i++) {
        clock_t begin = clock();
        #pragma omp parallel for  // Indicação de laço a ser otimizado
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                map_elevation[x * HEIGHT + y] = 1 * noise(1 * x, 1 * y) +
                                                0.5 * noise(2 * x, 2 * y) +
                                                0.25 * noise(4 * x, 2 * y);
                map_biome[x * HEIGHT + y] = biome(noise(x, y));
            }
        }
        clock_t end = clock();
        printf("%lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
    }
    return 0;
}
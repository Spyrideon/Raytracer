#include "rt_math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Screen.h"

constexpr int WIDTH = 100;
constexpr int HEIGTH = 100;

int main() {
  Screen screen(WIDTH, HEIGTH);

  for (int y = 0; y < HEIGTH; y++) {
    for (int x = 0; x < WIDTH; x++) {
      screen.writePixel(x, y, 255, 100, 100);
    }
  }

  screen.save("../output/render.ppm");


  return 0;
}


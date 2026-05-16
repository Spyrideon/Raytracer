#ifndef RAYTRACER_SCREEN_H
#define RAYTRACER_SCREEN_H
#include <vector>
#include <string>
#include <fstream>

class Screen {
    const int width, height;
    struct Pixel { uint8_t r, g, b; };
    std::vector<Pixel> pixels;
public:

    Screen(int width, int height);

    void writePixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void save(const std::string& path) const;

};

#endif //RAYTRACER_SCREEN_H
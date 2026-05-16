#include "Screen.h"

Screen::Screen(const int width, const int height) :
        width(width), height(height),
        pixels(width * height, {0, 0, 0}) { }



void Screen::writePixel(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b) {
    pixels[y * width + x] = {r, g, b};
}

void Screen::save(const std::string& path) const {
    std::ofstream file(path, std::ios::binary);
    file << "P6\n" << width << " " << height << "\n255\n";
    for (const auto& p : pixels)
        file.write(reinterpret_cast<const char*>(&p), 3);
}
#pragma once

#include <vector>
#include <iostream>
#include <vector>
#include "../objects/Color.hpp"

class Image
{
private:
    unsigned int width = 0;
    std::vector<Color> buffer;
    unsigned int height = 0;

public:
    Image(unsigned int w, unsigned int h);
    Image(unsigned int w, unsigned int h, Color c);
    ~ Image();

    void set_pixel(unsigned int x, unsigned int y, Color color);
    Color get_pixel(unsigned int x, unsigned int y);

    void write_file(const char* filename);
};

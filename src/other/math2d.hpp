#ifndef OTHER_MATH2D_HPP
#define OTHER_MATH2D_HPP

#include <cstddef>

struct Vector2 {
    int x;
    int y;

    Vector2(int x, int y);
    Vector2();
};

struct Dim2 {
    std::size_t width;
    std::size_t height;

    Dim2(std::size_t w, std::size_t h);
    Dim2();
};

#endif

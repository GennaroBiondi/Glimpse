#include "other/math2d.hpp"

Dim2::Dim2() : width(0), height(0) {}
Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(int x, int y) : x(x), y(y) {}
Dim2::Dim2(std::size_t w, std::size_t h) : width(w), height(h) {}

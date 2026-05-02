#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include "other/math2d.hpp"
#include <SDL.h>
#include <SDL_video.h>
#include <string>
#include <string_view>

struct Window {
    SDL_Window *window;
    Vector2 position;
    Dim2 dimension;
    std::string name;

    Window(const Vector2 &vec2, const Dim2 &dim, std::string_view name);

    void display_window();
};

#endif

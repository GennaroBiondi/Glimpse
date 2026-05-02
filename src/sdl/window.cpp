#include "sdl/window.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_video.h>
#include <stdexcept>

Window::Window(const Vector2 &vec2, const Dim2 &dim, std::string_view name)
    : position(vec2), dimension(dim), name(name) {}

void Window::display_window() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(std::string("Failed to init SDL: ") +
                                 SDL_GetError());
    this->window =
        SDL_CreateWindow(this->name.c_str(), this->position.x, this->position.y,
                         this->dimension.width, this->dimension.height, 0);

    if (!this->window) {
        throw std::runtime_error(std::string("Failed to open window. Error: ") +
                                 SDL_GetError());
    }
}

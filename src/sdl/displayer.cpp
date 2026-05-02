#include "image/image_displayer.hpp"
#include "image/image_info.hpp"
#include "other/math2d.hpp"
#include "window.hpp"
#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <filesystem>
#include <stdexcept>

namespace Displayer {
void display_image(const std::filesystem::path &path, const ImageInfo &info) {
    Vector2 center_vec(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    Dim2 window_size(info.dimension.width, info.dimension.height);
    Window window(center_vec, window_size, info.name);

    window.display_window();
    SDL_Surface *psurface = SDL_GetWindowSurface(window.window);
    if (!psurface) {
        throw std::runtime_error(
            std::string("Failed to create window surface. Error: ") +
            SDL_GetError());
    }

    ImageDisplayer::display(psurface, info);

    SDL_UpdateWindowSurface(window.window);

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                running = 0;
                break;
            }
        }
        SDL_Delay(10);
    }
}
} // namespace Displayer

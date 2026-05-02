#include "image/image_info.hpp"
#include "other/math2d.hpp"
#include "window.hpp"
#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <filesystem>
#include <fstream>
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

    std::ifstream img_file(path);
    SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
    for (int y = 0; y < window.dimension.height; y++) {
        for (int x = 0; x < window.dimension.width; x++) {
            Uint8 r, g, b;
            img_file.read(reinterpret_cast<char *>(&r), 1);
            img_file.read(reinterpret_cast<char *>(&g), 1);
            img_file.read(reinterpret_cast<char *>(&b), 1);
            Uint32 color = SDL_MapRGB(psurface->format, r, g, b);
            pixel.x = x;
            pixel.y = y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(window.window);
}
} // namespace Displayer

#include "image_displayer.hpp"
#include "image/image_info.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <cstring>
#include <fstream>
#include <string>

namespace ImageDisplayer {

static void blit_surface(SDL_Surface *dst, SDL_Surface *src, std::size_t max_w,
                         std::size_t max_h) {
    if (!src)
        return;
    SDL_Rect region = {0, 0, static_cast<int>(max_w), static_cast<int>(max_h)};
    SDL_BlitSurface(src, &region, dst, nullptr);
    SDL_FreeSurface(src);
}

static void blit_ppm(SDL_Surface *surface, const std::filesystem::path &path,
                     std::size_t max_w, std::size_t max_h) {
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return;

    auto skip_comments = [&]() {
        while (file.peek() == '#') {
            std::string line;
            std::getline(file, line);
        }
    };

    std::string magic;
    int w, h, maxval;

    skip_comments();
    file >> magic;
    skip_comments();
    file >> w;
    skip_comments();
    file >> h;
    skip_comments();
    file >> maxval;
    file.ignore(1);

    if (magic != "P6" || w <= 0 || h <= 0)
        return;

    SDL_Surface *tmp =
        SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
    if (!tmp)
        return;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            uint8_t rgb[3];
            file.read(reinterpret_cast<char *>(rgb), 3);
            if (!file) {
                SDL_FreeSurface(tmp);
                return;
            }
            uint32_t pixel =
                SDL_MapRGBA(tmp->format, rgb[0], rgb[1], rgb[2], 0xFF);
            uint8_t *dst = static_cast<uint8_t *>(tmp->pixels) +
                           y * tmp->pitch + x * tmp->format->BytesPerPixel;
            std::memcpy(dst, &pixel, tmp->format->BytesPerPixel);
        }
    }

    blit_surface(surface, tmp, max_w, max_h);
}

void display(SDL_Surface *surface, const ImageInfo &info) {
    using Format = ImageFormat::Format;

    const auto w = info.dimension.width;
    const auto h = info.dimension.height;

    switch (info.format) {
    case Format::PNG:
    case Format::JPG:
        blit_surface(surface, IMG_Load(info.path.c_str()), w, h);
        break;
    case Format::PPM:
        blit_ppm(surface, info.path, w, h);
        break;
    case Format::UNKNOWN:
        break;
    }
}

} // namespace ImageDisplayer

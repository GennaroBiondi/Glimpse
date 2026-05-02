#ifndef SDL_DISPLAYER_HPP
#define SDL_DISPLAYER_HPP

#include "image/image_info.hpp"
#include <filesystem>

namespace Displayer {
void display_image(const std::filesystem::path &path, const ImageInfo &info);
}

#endif

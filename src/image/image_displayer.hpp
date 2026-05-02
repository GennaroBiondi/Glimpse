#ifndef IMAGE_DISPLAYER_HPP
#define IMAGE_DISPLAYER_HPP

#include "image/image_info.hpp"
#include <SDL.h>
#include <SDL_surface.h>

namespace ImageDisplayer {
void display(SDL_Surface *surface, const ImageInfo &info);
}

#endif

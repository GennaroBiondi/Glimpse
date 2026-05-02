#ifndef IMAGE_READER_HPP
#define IMAGE_READER_HPP

#include "image_info.hpp"
#include <filesystem>

namespace ImageReader {
ImageInfo get_image_info(const std::filesystem::path &path);
}

#endif

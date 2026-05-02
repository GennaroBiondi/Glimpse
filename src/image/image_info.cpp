#include "image_info.hpp"
#include "image_format.hpp"
#include <filesystem>
#include <iostream>

ImageInfo::ImageInfo(const Dim2 &d, const ImageFormat::Format f,
                     const std::filesystem::path &path, std::string_view name)
    : dimension(d), format(f), path(path), name(name) {}

ImageInfo::ImageInfo()
    : dimension{}, format(ImageFormat::Format::UNKNOWN), path{}, name{} {}

void ImageInfo::output_info() {
    std::cout << this->name << " info:\n";
    std::cout << "- size:       " << this->dimension.width << "x"
              << this->dimension.height << "\n";
    std::cout << "- format:     " << ImageFormat::format_to_string(this->format)
              << "\n";
    std::cout << "- path:       " << this->path << "\n";
}

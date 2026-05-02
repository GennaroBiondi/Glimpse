#ifndef IMAGE_INFO_HPP
#define IMAGE_INFO_HPP

#include "image_format.hpp"
#include "other/math2d.hpp"
#include <string>
#include <string_view>

struct ImageInfo {
    Dim2 dimension;
    ImageFormat::Format format;
    std::string name;

    ImageInfo(const Dim2 &d, const ImageFormat::Format f,
              std::string_view name);
    ImageInfo();

    void output_info();
};

#endif

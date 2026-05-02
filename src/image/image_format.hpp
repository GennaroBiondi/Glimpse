#ifndef IMAGE_FORMAT_HPP
#define IMAGE_FORMAT_HPP

#include <filesystem>
#include <string_view>

namespace ImageFormat {
enum class Format {
    PNG,
    JPG,
    PPM,
    UNKNOWN,
};

std::string format_to_string(const Format &format);
Format get_format_from_image(const std::filesystem::path &path);
Format get_format_from_ext(std::string_view ext);
} // namespace ImageFormat

#endif

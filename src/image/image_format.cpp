#include "image_format.hpp"
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string_view>

using Format = ImageFormat::Format;

Format ImageFormat::get_format_from_image(const std::filesystem::path &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file to get format");
    }

    std::uint8_t header[8]{};
    file.read(reinterpret_cast<char *>(header), 8);

    // ---------------- PNG ----------------
    const std::uint8_t png_sig[8] = {0x89, 'P',  'N',  'G',
                                     0x0D, 0x0A, 0x1A, 0x0A};

    if (std::memcmp(header, png_sig, 8) == 0) {
        return Format::PNG;
    }

    // ---------------- JPG ----------------
    // JPEG starts with FF D8 FF
    if (header[0] == 0xFF && header[1] == 0xD8) {
        return Format::JPG;
    }

    // ---------------- PPM ----------------
    // PPM (P6 or P3) starts with ASCII "P6" or "P3"
    if (header[0] == 'P' && (header[1] == '6' || header[1] == '3')) {
        return Format::PPM;
    }

    return Format::UNKNOWN;
}

Format ImageFormat::get_format_from_ext(std::string_view ext) {
    if (ext == "png" || ext == ".png")
        return Format::PNG;
    else if (ext == "jpg" || ext == "jpeg" || ext == ".jpg" || ext == ".jpeg")
        return Format::JPG;
    else if (ext == "ppm" || ext == ".ppm")
        return Format::PPM;
    else
        return Format::UNKNOWN;
}

std::string ImageFormat::format_to_string(const Format &format) {
    static const char *lut[] = {"PNG", "JPG", "PPM", "UNKNOWN"};

    return lut[static_cast<int>(format)];
}

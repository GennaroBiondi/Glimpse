#include "image_reader.hpp"
#include "image/image_format.hpp"
#include "image_info.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

std::uint32_t read_be_u32(const std::uint8_t *p) {
    return (static_cast<std::uint32_t>(p[0]) << 24) |
           (static_cast<std::uint32_t>(p[1]) << 16) |
           (static_cast<std::uint32_t>(p[2]) << 8) |
           (static_cast<std::uint32_t>(p[3]));
}

static void read_exact(std::ifstream &file, std::uint8_t *buf, std::size_t n) {
    file.read(reinterpret_cast<char *>(buf), n);
    if (!file) {
        throw std::runtime_error("unexpected EOF while reading file");
    }
}

namespace ImageReader {

ImageInfo get_image_info(const fs::path &path) {
    ImageInfo info;
    info.name = path.filename().string();

    ImageFormat::Format format = ImageFormat::get_format_from_image(path);

    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("failed to open file");
    }

    if (format == ImageFormat::Format::PNG) {
        std::uint8_t sig[8]{};
        read_exact(file, sig, 8);

        std::uint8_t len[4]{};
        std::uint8_t type[4]{};

        read_exact(file, len, 4);
        read_exact(file, type, 4);

        if (!(type[0] == 'I' && type[1] == 'H' && type[2] == 'D' &&
              type[3] == 'R')) {
            throw std::runtime_error("invalid PNG: missing IHDR");
        }

        std::uint8_t ihdr[13]{};
        read_exact(file, ihdr, 13);

        info.format = format;
        info.dimension.width = read_be_u32(ihdr + 0);
        info.dimension.height = read_be_u32(ihdr + 4);

        return info;
    }

    if (format == ImageFormat::Format::JPG) {
        file.clear();
        file.seekg(0);

        while (file) {
            std::uint8_t marker[2]{};
            read_exact(file, marker, 2);

            if (marker[0] != 0xFF)
                break;

            std::uint8_t len[2]{};
            read_exact(file, len, 2);
            std::uint16_t segment_size = (len[0] << 8) | len[1];

            if (marker[1] == 0xC0 || marker[1] == 0xC2) {
                std::uint8_t data[5]{};
                read_exact(file, data, 5);

                std::uint16_t height = (data[1] << 8) | data[2];
                std::uint16_t width = (data[3] << 8) | data[4];

                info.format = format;
                info.dimension.width = width;
                info.dimension.height = height;

                return info;
            }

            file.seekg(segment_size - 2, std::ios::cur);
        }

        throw std::runtime_error("invalid JPEG: SOF not found");
    }

    if (format == ImageFormat::Format::PPM) {
        file.seekg(0);

        std::string magic;
        file >> magic;

        if (magic != "P6") {
            throw std::runtime_error("unsupported PPM format");
        }

        int width = 0;
        int height = 0;
        int maxval = 0;

        file >> width >> height >> maxval;
        file.get();

        info.format = format;
        info.dimension.width = width;
        info.dimension.height = height;

        return info;
    }

    throw std::runtime_error("unsupported or invalid image format");
}

} // namespace ImageReader

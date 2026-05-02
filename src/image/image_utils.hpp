#ifndef IMAGE_UTILS_HPP
#define IMAGE_UTILS_HPP

#include <filesystem>

namespace ImageUtils {
enum class ImageCheckResult {
    VALID,
    PATH_NONEXISTENT,
    PATH_NOT_REGULAR_FILE,
    PATH_NOT_IMG_FILE,
};

ImageCheckResult validate_image_path(const std::filesystem::path &img_path);
} // namespace ImageUtils

#endif

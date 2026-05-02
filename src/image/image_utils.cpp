#include "image_utils.hpp"
#include "image_format.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using ics = ImageUtils::ImageCheckResult;

// Validate an image file
//
// Returns an ImageUtils::ImageCheckResult,
// Here are all return cases:
// - Path doesn't point to anything on filesystem
// (ImageCheckResult::PATH_NONEXISTENT)
// - Path doesn't point to a regular file
// (ImageCheckResult::PATH_NOT_REGULAR_FILE)
// - Path doesn't point to an image file, checked by extension
// (ImageCheckResult::PATH_NOT_IMG_FILE)
//
// if the given path points to an image, the function returns
// ImageCheckResult::VALID.
ics ImageUtils::validate_image_path(const fs::path &img_path) {
    if (!fs::exists(img_path)) {
        return ics::PATH_NONEXISTENT;
    }

    if (!fs::is_regular_file(img_path)) {
        return ics::PATH_NOT_REGULAR_FILE;
    }

    std::string ext = img_path.extension().string();
    if (ImageFormat::get_format_from_ext(ext) == ImageFormat::Format::UNKNOWN) {
        return ics::PATH_NOT_IMG_FILE;
    }

    return ics::VALID;
}

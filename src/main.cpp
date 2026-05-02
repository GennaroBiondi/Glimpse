#include "app/usage.hpp"
#include "image/image_info.hpp"
#include "image/image_reader.hpp"
#include "image/image_utils.hpp"
#include "sdl/displayer.hpp"
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

using path = std::filesystem::path;

// guarantees the image path that is given is an
// image file and exists
//
// Throws if:
// - Image path doesn't point to a file (std::runtime_error)
// - Image path doesn't point to a regular file in the fs (std::runtime_error)
// - Image path doesn't point to an image file in the fs (std::runtime_error)
void handle_path_input(std::string_view img_path) {
    switch (ImageUtils::validate_image_path(img_path)) {
    case ImageUtils::ImageCheckResult::PATH_NONEXISTENT:
        throw std::runtime_error(
            "Image path doesn't exist, are you sure the path is correct?");
        break;
    case ImageUtils::ImageCheckResult::PATH_NOT_REGULAR_FILE: {
    }
    case ImageUtils::ImageCheckResult::PATH_NOT_IMG_FILE: {
        throw std::runtime_error(
            "Image path isn't an image or isn't supported");
        break;
    }
    case ImageUtils::ImageCheckResult::VALID: {
        break;
    }
    }
}

int main(int argc, char **argv) {
    std::string command;
    if (argc < 2) {
        std::cout << "Please enter command:\n";
        std::cout << "> ";
        std::cin >> command;
    } else {
        command = std::string(argv[1]);
    }

    if (command != "view" && command != "check" && command != "help") {
        std::cerr << "Invalid command!\n";
        return 1;
    }

    if (command == "help") {
        print_usage();
        return 0;
    }

    std::string img_path_str;
    if (argc < 3) {
        std::cout << "Please enter image path:\n";
        std::cout << "> ";
        std::cin >> img_path_str;
    } else {
        img_path_str = std::string(argv[2]);
    }

    path img_path(img_path_str);

    try {
        handle_path_input(img_path_str);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    ImageInfo info = ImageReader::get_image_info(img_path);

    if (command == "check") {
        info.output_info();
        return 0;
    }

    Displayer::display_image(img_path, info);

    return 0;
}

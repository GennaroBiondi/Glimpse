#include "info.hpp"
#include <iostream>

void print_usage() {
    std::cout << "\nGlimpse v" << App::PROGRAM_VERSION << "\n";
    std::cout << "'image viewer that gives you a glimpse of perfection'\n\n";
    std::cout << "Usage:\n";
    std::cout << "	glimpse [COMMAND] [IMAGE_PATH]\n\n";
    std::cout << "Commands:\n";
    std::cout << "	check: analyzes the image given and outputs info about the "
                 "image\n";
    std::cout << "	view: opens the image into a new window\n";
    std::cout << "	help: outputs this help message\n\n";
}

//
// Created by fpeterek on 28.10.21.
//

#include "util.hpp"


sf::Image loadImage(const std::string & filename) {
    sf::Image img;
    if (not img.loadFromFile(filename)) {
        throw std::runtime_error("Could not load file " + filename);
    }

    return img;
}

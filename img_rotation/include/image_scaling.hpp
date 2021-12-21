//
// Created by fpeterek on 21.12.21.
//

#ifndef IMG_ROTATION_IMAGE_SCALING_HPP
#define IMG_ROTATION_IMAGE_SCALING_HPP

#include <functional>

#include <SFML/Graphics.hpp>

#include "pixel_approximation.hpp"


sf::Image scale(const sf::Image & img, float ratio, const PixelFun & fn = nearestNeighbour);

#endif //IMG_ROTATION_IMAGE_SCALING_HPP

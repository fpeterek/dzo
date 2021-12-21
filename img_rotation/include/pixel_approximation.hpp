//
// Created by fpeterek on 20.12.21.
//

#ifndef IMG_ROTATION_PIXEL_APPROXIMATION_HPP
#define IMG_ROTATION_PIXEL_APPROXIMATION_HPP

#include <cmath>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "util.hpp"

typedef std::function<sf::Color(const sf::Image&, sf::Vector2f)> PixelFun;


sf::Color nearestNeighbour(const sf::Image & img, sf::Vector2f pixelPos);
sf::Color bilinearInterpolation(const sf::Image & img, sf::Vector2f pixelPos);
// Commented out until I actually create the function
// sf::Color bicubicInterpolation(const sf::Image & img, sf::Vector2f pixelPos);

#endif //IMG_ROTATION_PIXEL_APPROXIMATION_HPP

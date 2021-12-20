//
// Created by fpeterek on 20.12.21.
//

#ifndef IMG_ROTATION_IMAGE_ROTATION_HPP
#define IMG_ROTATION_IMAGE_ROTATION_HPP

#include <cmath>
#include <tuple>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "pixel_approximation.hpp"


sf::Vector2f rotate(sf::Vector2f point, sf::Vector2f pivot, float phi);

struct RotatedImgBounds {
    const float minX;
    const float minY;
    const float maxX;
    const float maxY;

    float width() const;
    float height() const;
};

RotatedImgBounds rotateRect(const std::array<sf::Vector2f, 4> & vertices, sf::Vector2f pivot, float angle);

std::pair<sf::IntRect, sf::Vector2f> calcRotatedImgDimensions(sf::Vector2u size, sf::Vector2f pivot, float angle);

sf::Image rotate(const sf::Image & img, const float angle, const PixelFun & fn = nearestNeighbour);

#endif //IMG_ROTATION_IMAGE_ROTATION_HPP

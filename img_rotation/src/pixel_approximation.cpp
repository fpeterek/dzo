//
// Created by fpeterek on 20.12.21.
//

#include "pixel_approximation.hpp"

#include <iostream>


sf::Color nearestNeighbour(const sf::Image & img, const sf::Vector2f pixelPos) {
    const sf::Vector2i rounded { (int)std::round(pixelPos.x), (int)std::round(pixelPos.y) };
    return getPixel(img, rounded);
}

sf::Color bilinearInterpolation(const sf::Image & img, const sf::Vector2f pixelPos) {

    // Numbers are rounded to zero, not down, which, in combination with just the addition
    // of the value of one breaks weight calculation for negative numbers
    // Thus, we must check whether we're dealing with positive or negative numbers
    // and adjust accordingly
    const bool xAboveZero = pixelPos.x >= 0;
    const bool yAboveZero = pixelPos.y >= 0;

    // If we're working with positive numbers, we increment the bottom and right coordinates by one
    // If we're dealing with negative numbers, we decrement the upper and left coordinates by one
    const sf::Vector2i lt { (int)pixelPos.x - 1*(not xAboveZero), (int)pixelPos.y - 1*(not yAboveZero) };
    const sf::Vector2i lb { (int)pixelPos.x - 1*(not xAboveZero), (int)pixelPos.y + 1*yAboveZero };
    const sf::Vector2i rt { (int)pixelPos.x + 1*xAboveZero, (int)pixelPos.y - 1*(not yAboveZero)};
    const sf::Vector2i rb { (int)pixelPos.x + 1*xAboveZero, (int)pixelPos.y + 1*yAboveZero };

    const double weight1 = (rt.x - pixelPos.x);
    const double weight2 = (pixelPos.x - lt.x);

    const sf::Color upperRow = (getPixel(img, lt) * weight1) + (getPixel(img, rt) * weight2);
    const sf::Color lowerRow = (getPixel(img, lb) * weight1) + (getPixel(img, rb) * weight2);

    const double yWeight1 = (lb.y - pixelPos.y);
    const double yWeight2 = (pixelPos.y - lt.y);

    return (upperRow * yWeight1) + (lowerRow * yWeight2);
}

sf::Color bicubicInterpolation(const sf::Image & img, const sf::Vector2f pixelPos) {

    // Numbers are rounded to zero, not down, which, in combination with just the addition
    // of the value of one breaks weight calculation for negative numbers
    // Thus, we must check whether we're dealing with positive or negative numbers
    // and adjust accordingly
    const bool xAboveZero = pixelPos.x >= 0;
    const bool yAboveZero = pixelPos.y >= 0;

    // If we're working with positive numbers, we increment the bottom and right coordinates by one
    // If we're dealing with negative numbers, we decrement the upper and left coordinates by one
    const sf::Vector2i lt { (int)pixelPos.x - 1*(not xAboveZero), (int)pixelPos.y - 1*(not yAboveZero) };
    const sf::Vector2i lb { (int)pixelPos.x - 1*(not xAboveZero), (int)pixelPos.y + 1*yAboveZero };
    const sf::Vector2i rt { (int)pixelPos.x + 1*xAboveZero, (int)pixelPos.y - 1*(not yAboveZero)};
    const sf::Vector2i rb { (int)pixelPos.x + 1*xAboveZero, (int)pixelPos.y + 1*yAboveZero };

    const double weight1 = (rt.x - pixelPos.x);
    const double weight2 = (pixelPos.x - lt.x);

    const sf::Color upperRow = (getPixel(img, lt) * weight1) + (getPixel(img, rt) * weight2);
    const sf::Color lowerRow = (getPixel(img, lb) * weight1) + (getPixel(img, rb) * weight2);

    const double yWeight1 = (lb.y - pixelPos.y);
    const double yWeight2 = (pixelPos.y - lt.y);

    return (upperRow * yWeight1) + (lowerRow * yWeight2);
}

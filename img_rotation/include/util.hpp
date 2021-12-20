//
// Created by fpeterek on 20.12.21.
//

#ifndef IMG_ROTATION_UTIL_HPP
#define IMG_ROTATION_UTIL_HPP

#include <ostream>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


template<typename T>
std::ostream & operator<<(std::ostream & os, const sf::Vector2<T> & vec) {
    return os << "{x: " << vec.x << ", y: " << vec.y << "}";
}


float calcDist(sf::Vector2f p1, sf::Vector2f p2);
float calcAngle(sf::Vector2f p1, sf::Vector2f p2);

bool inImg(const sf::Image & img, sf::Vector2i pixelPos);

std::uint8_t clampColor(int orig);

sf::Color getPixel(const sf::Image & img, sf::Vector2i pixelPos);
sf::Color operator*(sf::Color color, double weight);

#endif //IMG_ROTATION_UTIL_HPP

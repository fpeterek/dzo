//
// Created by fpeterek on 20.12.21.
//

#include "util.hpp"


float calcDist(const sf::Vector2f p1, const sf::Vector2f p2) {
    const auto dx = p1.x - p2.x;
    const auto dy = p1.y - p2.y;
    return std::sqrt(dx*dx + dy*dy);
}

float calcAngle(const sf::Vector2f p1, const sf::Vector2f p2) {
    // Handle corner cases
    if (p1.x == p2.x) {
        if (p1.y == p2.y) {
            return 0;
        }
        if (p1.y < p2.y) {
            return M_PI * 1.5;
        }
        return M_PI_2;
    }
    if (p1.y == p2.y) {
        if (p1.x < p2.x) {
            return 0;
        }
        return M_PI;
    }

    const auto dist = calcDist(p1, p2);
    const auto cos = (p2.x - p1.x) / dist;
    const auto acos = std::acos(cos);
    return (p1.y > p2.y) ? acos : (2*M_PI - acos);
}

bool inImg(const sf::Image & img, const sf::Vector2i pixelPos) {
    return 0 <= pixelPos.x and pixelPos.x < img.getSize().x and
           0 <= pixelPos.y and pixelPos.y < img.getSize().y;
}

sf::Color getPixel(const sf::Image & img, const sf::Vector2i pixelPos) {
    if (inImg(img, pixelPos)) {
        return img.getPixel(pixelPos.x, pixelPos.y);
    }
    return sf::Color::Transparent;
}


uint8_t clampColor(const int orig) {
    return (uint8_t)std::min(255, std::max(0, orig));
}

sf::Color operator*(const sf::Color color, const double weight) {
    return {
        clampColor(std::round(int(color.r) * weight)),
        clampColor(std::round(int(color.g) * weight)),
        clampColor(std::round(int(color.b) * weight)),
        clampColor(std::round(int(color.a) * weight))
    };
}

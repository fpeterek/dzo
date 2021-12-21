//
// Created by fpeterek on 21.12.21.
//

#ifndef IMG_ROTATION_DISTORTION_CORRECTION_HPP
#define IMG_ROTATION_DISTORTION_CORRECTION_HPP

#include <SFML/Graphics.hpp>

sf::Image removeDistortion(const sf::Image & img, double coeff1, double coeff2);

#endif //IMG_ROTATION_DISTORTION_CORRECTION_HPP

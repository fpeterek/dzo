//
// Created by fpeterek on 21.12.21.
//

#include "distortion_correction.hpp"

#include <cmath>

#include "pixel_approximation.hpp"


std::pair<double, double> getCenter(const sf::Image & img) {
    return { img.getSize().x / 2.0, img.getSize().y / 2.0 };
}


sf::Image removeDistortion(const sf::Image & img, const double coeff1, const double coeff2) {
    sf::Image target;
    target.create(img.getSize().x, img.getSize().y);

    const auto [cx, cy] = getCenter(img);
    const auto r = std::sqrt(cx*cx + cy*cy);

    for (uint y = 0; y < img.getSize().y; ++y) {
        for (uint x = 0; x < img.getSize().x; ++x) {
            const auto adjustedX = (x - cx) / r;
            const auto adjustedY = (y - cy) / r;

            const auto rad = adjustedX*adjustedX + adjustedY*adjustedY;

            const float origX = cx + (x-cx) / (1 + coeff1 * rad + coeff2 * rad*rad);
            const float origY = cy + (y-cy) / (1 + coeff1 * rad + coeff2 * rad*rad);

            target.setPixel(x, y, bilinearInterpolation(img, { origX, origY }));
        }
    }

    return target;
}

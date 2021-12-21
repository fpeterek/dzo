//
// Created by fpeterek on 21.12.21.
//

#include "image_scaling.hpp"


sf::Image scale(const sf::Image & img, float ratio, const PixelFun & fn) {

    sf::Vector2u dim(img.getSize().x * ratio, img.getSize().y * ratio);

    sf::Image target;
    target.create(dim.x, dim.y);

    for (uint y = 0; y < dim.y; ++y) {
        for (uint x = 0; x < dim.x; ++x) {
            target.setPixel(x, y, fn(img, { x / ratio, y / ratio }));
        }
    }

    return target;
}

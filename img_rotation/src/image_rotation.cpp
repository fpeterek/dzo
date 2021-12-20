//
// Created by fpeterek on 20.12.21.
//

#include "image_rotation.hpp"

#include "util.hpp"


sf::Vector2f rotate(const sf::Vector2f point, const sf::Vector2f pivot, const float phi) {

    const auto alpha = calcAngle(pivot, point);
    const auto dist = calcDist(pivot, point);
    const auto angle = alpha + phi;

    return { dist * std::cos(angle), -1 * dist * std::sin(angle) };
}

float RotatedImgBounds::width() const {
    return std::abs(maxX - minX);
}

float RotatedImgBounds::height() const {
    return std::abs(maxY - minY);
}

RotatedImgBounds rotateRect(const std::array<sf::Vector2f, 4> & vertices, const sf::Vector2f pivot, const float angle) {
    const auto lt = rotate(vertices[0], pivot, angle);
    const auto lb = rotate(vertices[1], pivot, angle);
    const auto rt = rotate(vertices[2], pivot, angle);
    const auto rb = rotate(vertices[3], pivot, angle);

    const auto maxX = std::max(std::max(lt.x, lb.x), std::max(rt.x, rb.x));
    const auto maxY = std::max(std::max(lt.y, lb.y), std::max(rt.y, rb.y));
    const auto minX = std::min(std::min(lt.x, lb.x), std::min(rt.x, rb.x));
    const auto minY = std::min(std::min(lt.y, lb.y), std::min(rt.y, rb.y));

    return { minX, minY, maxX, maxY };
}

std::pair<sf::IntRect, sf::Vector2f> calcRotatedImgDimensions(const sf::Vector2u size, const sf::Vector2f pivot, const float angle) {

    // We do not subtract one because we want to work with img dimensions, not pixel positions
    // and subtracting one would make the image one pixel too small
    const auto imgDim = rotateRect(
       std::array<sf::Vector2f, 4> {
           sf::Vector2f { 0.f, 0.f }, { 0.f, (float)(size.y) },
           { (float)(size.x), 0.f }, { (float)(size.x), (float)(size.y) }
       },
       pivot, angle
    );

    // However, we are working with pixel positions, not img dimensions in this case,
    // As what we are trying to accomplish is computing the position of the pivot
    // in the rotated img
    // The first point in the right bottom corner has coordinates [width-1, height-1],
    // we want to take this into account when calculating pivot position,
    // otherwise, the pivot would be incorrectly offset
    const auto pivotDim = rotateRect(
        std::array<sf::Vector2f, 4> {
            sf::Vector2f { 0.f, 0.f }, { 0.f, (float)(size.y-1) },
            { (float)(size.x-1), 0.f }, { (float)(size.x-1), (float)(size.y-1) }
        },
        pivot, angle
    );

    return {
        {
            0,
            0,
            (int)std::round(imgDim.width()),
            (int)std::round(imgDim.height())
        },
        {
            std::abs(pivotDim.minX),
            std::abs(pivotDim.minY)
        }
    };
}

sf::Image rotate(const sf::Image & img, const float angle, const PixelFun & fn) {

    // The pivot's location might change during rotation, thus, we
    // must also obtain the new location of what was the pivot when rotating
    // the image, so that we can perform the rotation in the opposite direction
    const auto [imgRect, pivot] = calcRotatedImgDimensions(img.getSize(), { 0.0, 0.0 }, angle);
    const sf::Vector2i imgDim { imgRect.width, imgRect.height };

    sf::Image target;
    target.create(imgDim.x, imgDim.y, sf::Color(0, 0, 0, 0));

    for (int y = 0; y < imgDim.y; ++y) {
        for (int x = 0; x < imgDim.x; ++x) {
            const auto origPx = rotate({ (float)x, (float)y }, pivot, -angle);
            target.setPixel(x, y, fn(img, origPx));
        }
    }

    return target;
}

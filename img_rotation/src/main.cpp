#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>


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

sf::Vector2f rotate(const sf::Vector2f point, const sf::Vector2f pivot, const float phi) {

    const auto alpha = calcAngle(pivot, point);
    const auto dist = calcDist(pivot, point);
    const auto angle = alpha + phi;

    return { dist * std::cos(angle), -1 * dist * std::sin(angle) };
}

std::pair<sf::IntRect, sf::Vector2f> calcRotatedImgDimensions(const sf::Vector2u size, const sf::Vector2f pivot, const float angle) {

    const auto lt = rotate({ 0.0, 0.0 }, pivot, angle);
    const auto lb = rotate({ 0.0, (float)size.y }, pivot, angle);
    const auto rt = rotate({ (float)size.x, 0.0 }, pivot, angle);
    const auto rb = rotate({ (float)size.x, (float)size.y }, pivot, angle);

    const auto maxX = std::max(std::max(lt.x, lb.x), std::max(rt.x, rb.x));
    const auto maxY = std::max(std::max(lt.y, lb.y), std::max(rt.y, rb.y));
    const auto minX = std::min(std::min(lt.x, lb.x), std::min(rt.x, rb.x));
    const auto minY = std::min(std::min(lt.y, lb.y), std::min(rt.y, rb.y));

    return {
        {
            (int) minX,
            (int) minY,
            (int) std::round(std::abs(maxX - minX)),
            (int) std::round(std::abs(maxY - minY))
        },
        {
            std::abs(minX),
            std::abs(minY)
        }
    };
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

sf::Color nearestNeighbour(const sf::Image & img, const sf::Vector2f pixelPos) {
    const sf::Vector2i rounded { (int)std::round(pixelPos.x), (int)std::round(pixelPos.y) };
    return getPixel(img, rounded);
}

sf::Color operator*(const sf::Color color, const double weight) {
    return {
        (uint8_t)std::round(color.r * weight),
        (uint8_t)std::round(color.g * weight),
        (uint8_t)std::round(color.b * weight),
        (uint8_t)std::round(color.a * weight)
    };
}

sf::Color xAxisBilinearInterpolation(const sf::Image & img, const sf::Vector2f pixelPos) {
    const sf::Vector2i left { (int)pixelPos.x, (int)pixelPos.y };
    const sf::Vector2i right { (int)pixelPos.x + 1, (int)pixelPos.y };

    const double weight1 = (right.x - pixelPos.x) / (right.x - left.x);
    const double weight2 = (pixelPos.x - left.x) / (right.x - left.x);

    return (getPixel(img, left) * weight1) + (getPixel(img, right) * weight2);
}

sf::Color yAxisBilinearInterpolation(const sf::Image & img, const sf::Vector2f pixelPos) {
    const sf::Vector2i top { (int)pixelPos.x, (int)pixelPos.y };
    const sf::Vector2i bottom { (int)pixelPos.x, (int)pixelPos.y + 1 };

    const double weight1 = (bottom.y - pixelPos.y) / (bottom.y - top.y);
    const double weight2 = (pixelPos.y - top.y) / (bottom.y - top.y);

    return (getPixel(img, top) * weight1) + (getPixel(img, bottom) * weight2);
}

sf::Color xyBilinearInterpolation(const sf::Image & img, const sf::Vector2f pixelPos) {

    const sf::Vector2i lt { (int)pixelPos.x, (int)pixelPos.y };
    const sf::Vector2i lb { (int)pixelPos.x, (int)pixelPos.y + 1 };
    const sf::Vector2i rt { (int)pixelPos.x + 1, (int)pixelPos.y };
    const sf::Vector2i rb { (int)pixelPos.x + 1, (int)pixelPos.y + 1 };

    const double weight1 = (rt.x - pixelPos.x) / (rt.x - lt.x);
    const double weight2 = (pixelPos.x - lt.x) / (rt.x - lt.x);

    const sf::Color column1 = (getPixel(img, lt) * weight1) + (getPixel(img, rt) * weight2);
    const sf::Color column2 = (getPixel(img, lb) * weight1) + (getPixel(img, rb) * weight2);

    const double yWeight1 = (lb.y - pixelPos.y) / (lb.y - lt.y);
    const double yWeight2 = (pixelPos.y - lt.y) / (lb.y - lt.y);

    return (column1 * yWeight1) + (column2 * yWeight2);
}

sf::Color bilinearInterpolation(const sf::Image & img, const sf::Vector2f pixelPos) {

    if (pixelPos.x == std::round(pixelPos.x) and pixelPos.y == std::round(pixelPos.y)) {
        return getPixel(img, { (int)pixelPos.x, (int)pixelPos.y });
    }
    if (pixelPos.x == std::round(pixelPos.x)) {
        return yAxisBilinearInterpolation(img, pixelPos);
    }
    if (pixelPos.y == std::round(pixelPos.y)) {
        return xAxisBilinearInterpolation(img, pixelPos);
    }

    return xyBilinearInterpolation(img, pixelPos);
}

typedef std::function<sf::Color(const sf::Image&, sf::Vector2f)> PixelFun;

sf::Image rotate(const sf::Image & img, const float angle, const PixelFun & fn = nearestNeighbour) {

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

int main(int argc, const char * argv[]) {
    sf::Image lena;
    lena.loadFromFile("resources/lena64.png");
    const auto pi2 = rotate(lena, M_PI * 0.5);
    pi2.saveToFile("pi2.png");
    const auto pi4 = rotate(lena, M_PI * 0.25);
    pi4.saveToFile("pi4.png");
    const auto pi3 = rotate(lena, M_PI * 0.33);
    pi3.saveToFile("pi3.png");


    const auto bi_pi2 = rotate(lena, M_PI * 0.5, bilinearInterpolation);
    bi_pi2.saveToFile("bi_pi2.png");
    const auto bi_pi4 = rotate(lena, M_PI * 0.25, bilinearInterpolation);
    bi_pi4.saveToFile("bi_pi4.png");
    const auto bi_pi3 = rotate(lena, M_PI * 0.33, bilinearInterpolation);
    bi_pi3.saveToFile("bi_pi3.png");
    const auto bi_pi13 = rotate(lena, M_PI * 1.33, bilinearInterpolation);
    bi_pi13.saveToFile("bi_pi13.png");
}

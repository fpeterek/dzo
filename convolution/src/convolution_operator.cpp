//
// Created by fpeterek on 10.10.21.
//

#include "convolution_operator.hpp"

#include <cmath>
#include <thread>


void ConvolutionOperator::applyToPixel(const size_t x, const size_t y) {
    const Mask & m = mask->get();
    const auto leftOffset = m.leftOffset();
    const auto topOffset = m.topOffset();

    const auto destX = x - leftOffset;
    const auto destY = y - topOffset;

    float r, g, b;
    r = g = b = 0.f;

    for (size_t dy = 0; dy < m.height(); ++dy) {
        for (size_t dx = 0; dx < m.width(); ++dx) {
            const auto origX = x - leftOffset + dx;
            const auto origY = y - topOffset + dy;

            const auto & pixel = orig.get().getPixel(origX, origY);
            const auto pixelMask = m[{dy, dx}];

            r += pixel.r * pixelMask;
            g += pixel.g * pixelMask;
            b += pixel.b * pixelMask;
        }
    }

    dest.setPixel(destX, destY, sf::Color(std::round(r), std::round(g), std::round(b)));
}

void ConvolutionOperator::applyMask(const std::pair<size_t, size_t> from, const std::pair<size_t, size_t> to) {
    for (size_t x = from.first; x < to.first; ++x) {
        for (size_t y = from.second; y < to.second; ++y) {
            applyToPixel(x, y);
        }
    }
}

void ConvolutionOperator::applyMask() {
    const auto & m = mask->get();
    const auto origWidth = orig.get().getSize().x;
    const auto origHeight = orig.get().getSize().y;

    const auto beginX = m.leftOffset();
    const auto beginY = m.topOffset();
    const auto lastX = origWidth - m.leftOffset();
    const auto lastY = origHeight - m.topOffset();
    const auto width = origWidth - 2 * m.leftOffset();
    const auto height = origHeight - 2 * m.topOffset();

    const auto middleX = beginX + width/2;
    const auto middleY = beginY + height/2;

    /*
    std::array<std::thread, 4> threads = {
        std::thread { [&]() { applyMask({ beginX, beginY }, { middleX, middleY }); } },
        std::thread { [&]() { applyMask({ middleX, beginY }, { lastX, middleY }); } },
        std::thread { [&]() { applyMask({ beginX, beginY }, { middleX, lastY }); } },
        std::thread { [&]() { applyMask({ middleX, middleY }, { lastX, lastY }); } },
    };


    std::for_each(threads.begin(), threads.end(), [](std::thread & t) { t.join(); });
    */

    applyMask({ beginX, beginY }, { lastX, lastY });
}

sf::Image ConvolutionOperator::apply(const Mask & m) {
    return operator()(m);
}

sf::Image ConvolutionOperator::operator()(const Mask & m) {
    mask = m;
    recreateDestImage();
    applyMask();
    return dest;
}

ConvolutionOperator::ConvolutionOperator(const sf::Image & orig) : orig(orig) { }

void ConvolutionOperator::recreateDestImage() {
    dest.create(
        orig.get().getSize().x - (mask->get().width()-1),
        orig.get().getSize().y - (mask->get().height()-1)
    );
}

sf::Image operator*(const sf::Image & orig, const Mask & mask) {
    return ConvolutionOperator(orig)(mask);
}

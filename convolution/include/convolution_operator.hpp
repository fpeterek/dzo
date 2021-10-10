//
// Created by fpeterek on 10.10.21.
//

#ifndef CONVOLUTION_CONVOLUTION_OPERATOR_HPP
#define CONVOLUTION_CONVOLUTION_OPERATOR_HPP

#include <functional>
#include <optional>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "mask.hpp"


class ConvolutionOperator {

    std::reference_wrapper<const sf::Image> orig;

    sf::Image dest;
    std::optional<std::reference_wrapper<const Mask>> mask;

    void recreateDestImage();
    void applyToPixel(size_t x, size_t y);
    void applyMask(std::pair<size_t, size_t> from, std::pair<size_t, size_t> to);
    void applyMask();

public:

    ConvolutionOperator(const sf::Image & orig);

    sf::Image apply(const Mask & mask);
    sf::Image operator()(const Mask & mask);
};

sf::Image operator*(const sf::Image & orig, const Mask & mask);

#endif //CONVOLUTION_CONVOLUTION_OPERATOR_HPP

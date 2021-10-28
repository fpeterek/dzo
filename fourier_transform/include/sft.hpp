//
// Created by fpeterek on 28.10.21.
//

#ifndef FOURIER_TRANSFORM_SFT_HPP
#define FOURIER_TRANSFORM_SFT_HPP

#include <complex>

#include <SFML/Graphics.hpp>

#include "matrix.hpp"
#include "util.hpp"

namespace sft {

    Matrix<std::complex<double>> fourierTransform(const sf::Image & img);
    sf::Image inverseFourier(const Matrix<std::complex<double>> & matrix);

}

#endif //FOURIER_TRANSFORM_SFT_HPP

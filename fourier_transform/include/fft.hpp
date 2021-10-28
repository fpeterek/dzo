//
// Created by fpeterek on 28.10.21.
//

#ifndef FOURIER_TRANSFORM_FFT_HPP
#define FOURIER_TRANSFORM_FFT_HPP

#include <complex>
#include <vector>

#include <SFML/Graphics.hpp>

#include "util.hpp"
#include "matrix.hpp"

namespace fft {

    enum class FourierTransformDirection {
        Forward = -1,
        Backward = 1
    };

    Matrix<std::complex<double>> fft(const sf::Image & img);
    sf::Image ifft(const Matrix<std::complex<double>> & matrix);
}

#endif //FOURIER_TRANSFORM_FFT_HPP

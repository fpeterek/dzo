//
// Created by fpeterek on 28.10.21.
//

#ifndef FOURIER_TRANSFORM_IMG_TRANSFORM_HPP
#define FOURIER_TRANSFORM_IMG_TRANSFORM_HPP

#include <complex>

#include <SFML/Graphics.hpp>

#include "matrix.hpp"


Matrix<double> powerSpectrum(const Matrix<std::complex<double>> & matrix);
Matrix<double> phaseShift(const Matrix<std::complex<double>> & matrix);

sf::Image powerSpectrumToImg(const Matrix<double> & matrix);
sf::Image phaseShiftToImg(const Matrix<double> & matrix);


#endif //FOURIER_TRANSFORM_IMG_TRANSFORM_HPP

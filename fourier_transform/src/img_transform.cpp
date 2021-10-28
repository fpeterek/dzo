//
// Created by fpeterek on 28.10.21.
//

#include "img_transform.hpp"


Matrix<double> powerSpectrum(const Matrix<std::complex<double>> & matrix) {

    Matrix<double> spectrum { matrix.width(), matrix.height() };

    for (size_t y = 0; y < matrix.height(); ++y) {
        for (size_t x = 0; x < matrix.width(); ++x) {
            const auto val = matrix.at(y, x);
            spectrum.at(y, x) = std::pow(std::abs(val), 2.0);
        }
    }

    return spectrum;
}

sf::Image powerSpectrumToImg(const Matrix<double> & matrix) {
    Matrix<double> log { matrix.width(), matrix.height() };
    sf::Image img;
    img.create(matrix.width(), matrix.height());

    double max = 0.0;
    const size_t xHalf = matrix.width() / 2;
    const size_t yHalf = matrix.height() / 2;

    // Calc log and find max
    for (size_t y = 0; y < matrix.height(); ++y) {
        for (size_t x = 0; x < matrix.width(); ++x) {
            const auto px = std::log(matrix.at(y, x) + 1.0);
            log.at(y, x) = px;
            max = std::max(px, max);
        }
    }

    // Normalize, swap quadrant, convert to RGB and store to image
    if (max > 0.0) {
        for (size_t y = 0; y < matrix.height(); ++y) {
            for (size_t x = 0; x < matrix.width(); ++x) {
                const auto yCoord = (y < yHalf) ? (y + yHalf) : (y - yHalf);
                const auto xCoord = (x < xHalf) ? (x + xHalf) : (x - xHalf);
                const auto px = uint8_t((log.at(y, x) / max) * 255);
                img.setPixel(xCoord, yCoord, { px, px, px });
            }
        }
    }

    return img;
}

Matrix<double> phaseShift(const Matrix<std::complex<double>> & matrix) {

    Matrix<double> ps { matrix.width(), matrix.height() };

    for (size_t y = 0; y < matrix.height(); ++y) {
        for (size_t x = 0; x < matrix.width(); ++x) {
            const auto val = matrix.at(y, x);
            ps.at(y, x) = std::atan(val.imag() / val.real());
        }
    }

    return ps;
}

sf::Image phaseShiftToImg(const Matrix<double> & matrix) {
    sf::Image img;
    img.create(matrix.width(), matrix.height());

    const size_t xHalf = matrix.width() / 2;
    const size_t yHalf = matrix.height() / 2;

    for (size_t y = 0; y < matrix.height(); ++y) {
        for (size_t x = 0; x < matrix.width(); ++x) {
            const auto val = uint8_t(((matrix.at(y, x) + M_PI_2) / M_PI) * 255);
            const auto yCoord = (y < yHalf) ? (y + yHalf) : (y - yHalf);
            const auto xCoord = (x < xHalf) ? (x + xHalf) : (x - xHalf);
            img.setPixel(xCoord, yCoord, { val, val, val });
        }
    }

    return img;
}

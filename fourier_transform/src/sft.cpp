//
// Created by fpeterek on 28.10.21.
//

#include "sft.hpp"

namespace sft {

    std::complex<double> fourierPixel(const sf::Image & img, const size_t ox, const size_t oy) {

        std::complex<double> sum { 0.0, 0.0 };

        const double frac = 1 / std::sqrt(img.getSize().x * img.getSize().y);
        const double width = img.getSize().x;
        const double height = img.getSize().y;

        for (size_t y = 0; y < img.getSize().y; ++y) {
            for (size_t x = 0; x < img.getSize().x; ++x) {
                // Convert the picture to a monochromatic image
                const auto pixel = img.getPixel(x, y);
                const double px = (pixel.r + pixel.g + pixel.b) / 3.0;

                const std::complex<double> exp = -1.0j * pi2 * (ox * x / width + oy * y / height);
                sum += px * frac * std::exp(exp);
            }
        }

        return sum;
    }


    Matrix<std::complex<double>> fourierTransform(const sf::Image & img) {
        Matrix<std::complex<double>> matrix { img.getSize().x, img.getSize().y };

        for (size_t y = 0; y < img.getSize().y; ++y) {
            for (size_t x = 0; x < img.getSize().x; ++x) {
                matrix.at(y, x) = fourierPixel(img, x, y);
            }
        }

        return matrix;
    }

    double invFourierPixel(const Matrix<std::complex<double>> & matrix, const size_t ox, const size_t oy) {

        const double frac = 1 / std::sqrt(matrix.width() * matrix.height());
        const double width = matrix.width();
        const double height = matrix.height();

        std::complex<double> color = 0;

        for (size_t y = 0; y < matrix.height(); ++y) {
            for (size_t x = 0; x < matrix.width(); ++x) {
                const auto val = matrix.at(y, x);

                const std::complex<double> exp = 1.0j * pi2 * (x * ox / width + y * oy / height);
                color += val * frac * std::exp(exp);
            }
        }

        return std::abs(color);
    }

    sf::Image inverseFourier(const Matrix<std::complex<double>> & matrix) {
        sf::Image img;
        img.create(matrix.width(), matrix.height());

        for (size_t y = 0; y < matrix.height(); ++y) {
            for (size_t x = 0; x < matrix.width(); ++x) {
                const auto px = uint8_t(invFourierPixel(matrix, x, y));
                img.setPixel(x, y, { px, px, px });
            }
        }

        return img;
    }

}

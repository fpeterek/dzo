//
// Created by fpeterek on 28.10.21.
//

#include "fft.hpp"

namespace fft {

    using FTD = FourierTransformDirection;

    void fft(std::vector<std::complex<double>> & vector, FTD dir = FTD::Forward) {

        if (vector.size() == 1) {
            return;
        }

        auto [even, odd] = split(vector);

        fft::fft(even, dir);
        fft::fft(odd, dir);

        for (size_t i = 0; i < vector.size()/2; ++i) {

            const auto p = even[i];
            const std::complex<double> exp = (int)dir * 1j * pi2 * i / vector.size();
            const auto q = std::exp(exp) * odd[i];

            vector[i] = p+q;
            vector[i + vector.size()/2] = p-q;
        }
    }

    Matrix<std::complex<double>> imgToMatrix(const sf::Image & img) {
        Matrix<std::complex<double>> matrix { img.getSize().x, img.getSize().y };
        const double frac = 1 / std::sqrt(matrix.width() * matrix.height());

        for (size_t y = 0; y < matrix.height(); ++y) {
            for (size_t x = 0; x < matrix.width(); ++x) {
                const auto px = img.getPixel(x, y);
                matrix.at(y, x) = ((px.r + px.g + px.b) / 3.0) * frac;
            }
        }

        return matrix;
    }

    Matrix<std::complex<double>> fft(const sf::Image & img) {

        auto matrix = imgToMatrix(img);

        for (size_t y = 0; y < matrix.height(); ++y) {
            auto row = matrix.row(y);
            fft(row);
            matrix.setRow(y, row);
        }
        for (size_t x = 0; x < matrix.width(); ++x) {
            auto col = matrix.col(x);
            fft(col);
            matrix.setCol(x, col);
        }

        return matrix;
    }

    sf::Image ifft(const Matrix<std::complex<double>> & matrix) {

        auto out = matrix;

        for (size_t y = 0; y < matrix.height(); ++y) {
            auto row = matrix.row(y);
            fft(row, FTD::Backward);
            out.setRow(y, row);
        }
        for (size_t x = 0; x < matrix.width(); ++x) {
            auto col = out.col(x);
            fft(col, FTD::Backward);
            out.setCol(x, col);
        }

        sf::Image img;
        img.create(matrix.width(), matrix.height());
        const double frac = 1 / std::sqrt(matrix.width() * matrix.height());

        for (size_t y = 0; y < matrix.height(); ++y) {
            for (size_t x = 0; x < matrix.width(); ++x) {
                const auto val = (uint8_t)std::abs(out.at(y, x) * frac);
                img.setPixel(x, y, { val, val, val });
            }
        }

        return img;
    }

}

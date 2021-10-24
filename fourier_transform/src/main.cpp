#include <iostream>
#include <cmath>
#include <complex>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "matrix.hpp"
#include "fs.hpp"


sf::Image loadImage(const std::string & filename) {
    sf::Image img;
    if (not img.loadFromFile(filename)) {
        throw std::runtime_error("Could not load file " + filename);
    }

    return img;
}

static constexpr double pi2 = 2 * M_PI;

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

            const std::complex<double> exp = -1.0j * pi2 * (ox*x/width + oy*y/height);
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

            const std::complex<double> exp = 1.0j * pi2 * (x*ox/width + y*oy/height);
            color += val * frac * std::exp(exp);
        }
    }

    return abs(color);
}

sf::Image inverseFourier(const Matrix<std::complex<double>> & matrix) {
    sf::Image img;
    img.create(matrix.width(), matrix.height());

    for (size_t y = 0; y < matrix.height(); ++y) {
        for (size_t x = 0; x < matrix.width(); ++x) {
            const auto px = u_char(invFourierPixel(matrix, x, y));
            img.setPixel(x, y, { px, px, px });
        }
    }

    return img;
}

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

std::string folderName(std::string imgName) {
    const auto lastSlash = imgName.find_last_of('/');

    if (lastSlash != std::string::npos) {
        imgName = imgName.substr(lastSlash);
    }

    const auto lastPeriod = imgName.find_last_of('.');

    if (lastPeriod != std::string::npos) {
        imgName = imgName.substr(0, lastPeriod);
    }

    return imgName;
}

void transformImage(const std::string & filename) {
    fs::mkdir("out/");

    const auto folder = "out/" + folderName(filename) + "/";
    fs::recreateDir(folder);

    auto lena = loadImage(filename);
    auto f = fourierTransform(lena);

    auto power = powerSpectrum(f);
    auto powerImg = powerSpectrumToImg(power);
    powerImg.saveToFile(folder + "power.png");

    auto phase = phaseShift(f);
    auto phaseImg = phaseShiftToImg(phase);
    phaseImg.saveToFile(folder + "phase.png");

    auto f75 = f.applyMask(circleMask(f, 0.25));
    inverseFourier(f75).saveToFile(folder + "75pct.png");
    auto f50 = f.applyMask(circleMask(f, 0.50));
    inverseFourier(f50).saveToFile(folder + "50pct.png");
    auto f25 = f.applyMask(circleMask(f, 0.75));
    inverseFourier(f25).saveToFile(folder + "25pct.png");

    auto invFourier = inverseFourier(f);
    invFourier.saveToFile(folder + "inverse_fourier.png");
}

int main(int argc, const char * argv[]) {

    for (int i = 1; i < argc; ++i) {
        transformImage(argv[i]);
    }

}

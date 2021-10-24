//
// Created by fpeterek on 23.10.21.
//

#ifndef FOURIER_TRANSFORM_MATRIX_HPP
#define FOURIER_TRANSFORM_MATRIX_HPP

#include <cstdint>
#include <vector>
#include <tuple>


template<typename T>
class Matrix {
public:
    typedef std::vector<std::vector<T>> MatrixType;

private:
    MatrixType _matrix;
    size_t _width;
    size_t _height;

public:
    Matrix(size_t width, size_t height);
    Matrix(const Matrix<T> & other);
    Matrix<T> & operator=(const Matrix<T> & other);
    Matrix(Matrix<T> && other) noexcept;
    Matrix<T> & operator=(Matrix<T> && other) noexcept;
    const MatrixType & matrix() const;
    size_t width() const;
    size_t height() const;

    const T & at(size_t y, size_t x) const;
    T & at(size_t y, size_t x);

    const T & operator[](std::pair<size_t, size_t> yx) const;
    T & operator[](std::pair<size_t, size_t> yx);

    Matrix<T> applyMask(const Matrix<double> & mask);
};

template<typename T>
Matrix<double> circleMask(const Matrix<T> & matrix, const double sizeRatio) {
    Matrix<double> mask { matrix.width(), matrix.height() };

    const double cx = matrix.width() / 2;
    const double cy = matrix.height() / 2;
    const double rad = std::max(cx, cy) * sizeRatio;

    for (size_t x = 0; x < matrix.width(); ++x) {
        for (size_t y = 0; y < matrix.height(); ++y) {
            const auto dx = cx - x;
            const auto dy = cy - y;
            const auto d = std::sqrt(dx*dy + dy*dy);
            mask.at(y, x) = d > rad;
        }
    }

    return mask;
}

template<typename T>
Matrix<T> Matrix<T>::applyMask(const Matrix<double> & mask) {

    if (mask.width() != width() or mask.height() != height()) {
        throw std::runtime_error("Mask dimensions must match matrix dimensions.");
    }

    Matrix<T> m = *this;

    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            m.at(y, x) = at(y, x) * mask.at(y, x);
        }
    }

    return m;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & other) : _matrix(other.matrix()), _width(other.width()), _height(other.height()) { }

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    _matrix = other._matrix;
    _width = other.width();
    _height = other.height();
}

template<typename T>
Matrix<T>::Matrix(size_t width, size_t height) : _width(width), _height(height) {
    _matrix.reserve(height);
    for (size_t i = 0; i < height; ++i) {
        _matrix.template emplace_back(width);
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept :
    _width(other._width), _height(other.height()), _matrix(std::move(other._matrix)) { }

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
    _width = other._width;
    _height = other.height();
    _matrix = std::move(other._matrix);
    return *this;
}

template<typename T>
const typename Matrix<T>::MatrixType & Matrix<T>::matrix() const {
    return _matrix;
}

template<typename T>
size_t Matrix<T>::width() const {
    return _width;
}

template<typename T>
size_t Matrix<T>::height() const {
    return _height;
}

template<typename T>
const T & Matrix<T>::at(const size_t y, const size_t x) const {
    return _matrix[y][x];
}

template<typename T>
T & Matrix<T>::at(const size_t y, const size_t x) {
    return _matrix[y][x];
}

template<typename T>
const T & Matrix<T>::operator[](const std::pair<size_t, size_t> yx) const {
    const auto [y, x] = yx;
    return at(y, x);
}

template<typename T>
T & Matrix<T>::operator[](const std::pair<size_t, size_t> yx) {
    const auto [y, x] = yx;
    return at(y, x);
}

#endif //FOURIER_TRANSFORM_MATRIX_HPP

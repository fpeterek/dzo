//
// Created by fpeterek on 23.10.21.
//

#ifndef FOURIER_TRANSFORM_MATRIX_HPP
#define FOURIER_TRANSFORM_MATRIX_HPP

#include <cstdint>
#include <vector>
#include <tuple>
#include <cmath>


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

    std::vector<T> row(size_t y) const;
    std::vector<T> col(size_t x) const;

    void setRow(size_t y, const std::vector<T> & row);
    void setCol(size_t x, const std::vector<T> & col);

    const T & at(size_t y, size_t x) const;
    T & at(size_t y, size_t x);

    const T & operator[](std::pair<size_t, size_t> yx) const;
    T & operator[](std::pair<size_t, size_t> yx);

    Matrix<T> applyMask(const Matrix<double> & mask);
};

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & mat) {
    for (size_t y = 0; y < mat.height(); ++y) {
        for (size_t x = 0; x < mat.width(); ++x) {
            os << mat.at(y, x);
        }
        if (y < mat.height()-1) {
            std::endl(os);
        }
    }

    return os;
}

template<typename T>
Matrix<double> circleMask(const Matrix<T> & matrix, const double sizeRatio) {
    Matrix<double> mask { matrix.width(), matrix.height() };

    const double cx = matrix.width() / 2;
    const double cy = matrix.height() / 2;
    const double rad = std::max(cx, cy) * sizeRatio;

    for (size_t x = 0; x < matrix.width(); ++x) {
        const auto dx = cx - x;
        const auto dx2 = dx*dx;
        for (size_t y = 0; y < matrix.height(); ++y) {
            const auto dy = cy - y;
            const auto d = std::sqrt(dx2 + dy*dy);
            mask.at(y, x) = d > rad;
        }
    }

    return mask;
}

template<typename T>
std::vector<T> Matrix<T>::row(const size_t y) const {
    return _matrix[y];
}

template<typename T>
std::vector<T> Matrix<T>::col(const size_t x) const {
    std::vector<T> out;
    out.reserve(height());

    for (size_t y = 0; y < height(); ++y) {
        out.template emplace_back(at(y, x));
    }

    return out;
}


template<typename T>
void Matrix<T>::setRow(size_t y, const std::vector<T> & row) {
    if (row.size() != width()) {
        throw std::runtime_error("Invalid size");
    }
    _matrix[y] = row;
}

template<typename T>
void Matrix<T>::setCol(size_t x, const std::vector<T> & col) {
    if (col.size() != height()) {
        throw std::runtime_error("Invalid size");
    }

    for (size_t y = 0; y < height(); ++y) {
        at(y, x) = col[y];
    }
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

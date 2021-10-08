//
// Created by fpeterek on 08.10.21.
//

#include "mask.hpp"

#include <fstream>
#include <sstream>
#include <iostream>


static std::vector<float> tokenize(const std::string & str) {
    std::vector<float> vec;
    std::stringstream ss(str);

    while (ss) {
        float f;
        ss >> f;
        vec.emplace_back(f);
        ss.ignore(1);
    }

    return vec;
}

static float sum(const std::vector<std::vector<float>> & mask) {

    float sum = 0.0;
    for (const auto & vec : mask) {
        for (const float coeff : vec) {
            sum += std::abs(coeff);
        }
    }

    return sum;
}

static auto normalize(const std::vector<std::vector<float>> & mask) {

    const float total = sum(mask);
    std::vector<std::vector<float>> copy = mask;

    if (total == 0) {
        return copy;
    }

    for (size_t y = 0; y < mask.size(); ++y) {
        for (size_t x = 0; x < mask.front().size(); ++x) {
            copy[y][x] /= total;
        }
    }

    return copy;
}

static std::string getMaskName(const std::string & filename) {
    const auto period = filename.find_last_of('.');
    const auto fslash = filename.find_last_of('/');
    const auto len = period - fslash;

    return filename.substr(fslash, len);
}

Mask Mask::loadFromFile(const std::string & filename) {
    std::ifstream in(filename);
    const auto maskname = getMaskName(filename);
    std::vector<std::vector<float>> result;

    while (in) {
        std::string line;
        std::getline(in, line);

        if (not line.empty()) {
            result.emplace_back(tokenize(line));
        }
    }

    return { normalize(result), maskname };
}

Mask::Mask(std::vector<std::vector<float>> mask, std::string name) : mask(std::move(mask)), _name(std::move(name)) { }

size_t Mask::width() const {
    return mask.empty() ? 0 : mask.front().size();
}

size_t Mask::height() const {
    return mask.size();
}

size_t Mask::leftOffset() const {
    return width() / 2;
}

size_t Mask::topOffset() const {
    return height() / 2;
}

float Mask::at(size_t y, size_t x) const {
    return mask[y][x];
}

float Mask::operator[](std::pair<size_t, size_t> idx) const {
    const auto [y, x] = idx;
    return at(y, x);
}

Mask::Mask(Mask && other) noexcept : mask(std::move(other.mask)), _name(std::move(other._name)) { }

Mask & Mask::operator=(Mask && other) noexcept {
    mask = std::move(other.mask);
    _name = std::move(other._name);
    return *this;
}

const std::string & Mask::name() const {
    return _name;
}


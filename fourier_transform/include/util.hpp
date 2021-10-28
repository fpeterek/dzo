//
// Created by fpeterek on 28.10.21.
//

#ifndef FOURIER_TRANSFORM_UTIL_HPP
#define FOURIER_TRANSFORM_UTIL_HPP

#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <stdexcept>
#include <exception>
#include <SFML/Graphics.hpp>


sf::Image loadImage(const std::string & filename);


constexpr double pi2 = M_PI * 2;


template<typename T>
std::pair<std::vector<T>, std::vector<T>> split(const std::vector<T> & vector) {

    std::vector<T> even;
    even.reserve(vector.size()/2);
    std::vector<T> odd;
    odd.reserve(vector.size()/2);

    for (size_t i = 0; i < vector.size(); i+=2) {
        even.emplace_back(vector[i]);
        odd.emplace_back(vector[i+1]);
    }

    return { std::move(even), std::move(odd) };
}

#endif //FOURIER_TRANSFORM_UTIL_HPP

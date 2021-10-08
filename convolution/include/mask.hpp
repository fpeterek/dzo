//
// Created by fpeterek on 08.10.21.
//

#ifndef CONVOLUTION_MASK_HPP
#define CONVOLUTION_MASK_HPP

#include <string>
#include <vector>


class Mask {

    std::vector<std::vector<float>> mask;
    std::string _name;

public:

    Mask(std::vector<std::vector<float>> mask, std::string name);
    Mask(Mask && other) noexcept;
    Mask & operator=(Mask && other) noexcept;

    static Mask loadFromFile(const std::string & filename);

    size_t width() const;
    size_t height() const;
    size_t leftOffset() const;
    size_t topOffset() const;

    float at(size_t y, size_t x) const;
    float operator[](std::pair<size_t, size_t> idx) const;

    const std::string & name() const;
};

#endif //CONVOLUTION_MASK_HPP

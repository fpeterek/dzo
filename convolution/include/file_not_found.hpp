//
// Created by fpeterek on 08.10.21.
//

#ifndef CONVOLUTION_FILE_NOT_FOUND_HPP
#define CONVOLUTION_FILE_NOT_FOUND_HPP

#include <stdexcept>

class FileNotFoundException : public std::runtime_error {
public:
    explicit FileNotFoundException(const std::string & filename);
};

#endif //CONVOLUTION_FILE_NOT_FOUND_HPP

//
// Created by fpeterek on 08.10.21.
//

#include "file_not_found.hpp"

FileNotFoundException::FileNotFoundException(const std::string & filename)
    : std::runtime_error("File not found: " + filename) { }


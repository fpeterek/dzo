//
// Created by fpeterek on 10.10.21.
//

#ifndef CONVOLUTION_FS_HPP
#define CONVOLUTION_FS_HPP

#include <string>
#include <vector>

namespace fs {
    std::vector <std::string> ls(const std::string & path);
    void mkdir(const std::string & path);
    void rmrf(const std::string & path);
    void recreateDir(const std::string & path);
}

#endif //CONVOLUTION_FS_HPP

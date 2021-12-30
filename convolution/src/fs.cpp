//
// Created by fpeterek on 10.10.21.
//

#include "fs.hpp"

#include <filesystem>


namespace fs {

    std::vector<std::string> ls(const std::string & path) {
        std::vector<std::string> contents;

        for (const auto & entry: std::filesystem::directory_iterator(path)) {
            contents.emplace_back(entry.path());
        }

        return contents;
    }

    void mkdir(const std::string & path) {
        if (not std::filesystem::exists(path)) {
            std::filesystem::create_directory(path);
        }
    }

    void rmrf(const std::string & path) {
        if (std::filesystem::exists(path)) {
            std::filesystem::remove_all(path);
        }
    }

    void recreateDir(const std::string & path) {
        rmrf(path);
        mkdir(path);
    }

}

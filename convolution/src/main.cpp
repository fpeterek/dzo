#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "file_not_found.hpp"
#include "mask.hpp"


std::vector<std::string> ls(const std::string & path) {
    std::vector<std::string> contents;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
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

std::vector<Mask> loadMasks(const std::string & path) {
    std::vector<Mask> masks;
    const auto files = ls(path);

    for (const auto & filename : files) {
        if (filename.rfind(".mask") == filename.size() - 5) {
            masks.emplace_back(Mask::loadFromFile(filename));
        }
    }

    return masks;
}

sf::Image loadImage(const std::string & infile) {
    sf::Image img;
    if (not img.loadFromFile(infile)) {
        throw FileNotFoundException(infile);
    }
    return img;
}

sf::Image applyMask(const sf::Image & orig, const Mask & mask) {

    sf::Image dest;
    dest.create(orig.getSize().x - (mask.width()-1), orig.getSize().y - (mask.height()-1));

    // TODO: Finish this function and I'm done
    return dest;
}

void process(const std::string & infile, const std::vector<Mask> & masks) {
    auto img = loadImage(infile);
    const auto outPath = "out/" + infile.substr(0, infile.find_last_of('.')) + "/";
    std::cout << outPath << std::endl;
    recreateDir(outPath);

    for (const Mask & mask : masks) {
        const auto newImage = applyMask(img, mask);
        newImage.saveToFile(outPath + mask.name() + ".png");
    }
}

void log(const FileNotFoundException & e) {
    std::cout << e.what() << std::endl;
}

void log(const std::exception & e) {
    std::cout << e.what() << std::endl;
    std::cout << "Unexpected error..." << std::endl;
}


int main(int argc, const char * argv[]) {
    mkdir("out/");
    const auto masks = loadMasks("masks/");

    for (int i = 1; i < argc; ++i) {
        try {
            process(argv[i], masks);
        } catch (const FileNotFoundException & e) {
            log(e);
        } catch (const std::exception & e) {
            log(e);
            return -1;
        }
    }
}

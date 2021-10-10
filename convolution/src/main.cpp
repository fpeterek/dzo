#include <iostream>
#include <filesystem>
#include <thread>

#include <SFML/Graphics.hpp>

#include "file_not_found.hpp"
#include "mask.hpp"
#include "fs.hpp"
#include "convolution_operator.hpp"


std::vector<Mask> loadMasks(const std::string & path) {
    std::vector<Mask> masks;
    const auto files = fs::ls(path);

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

std::string formOutPath(const std::string & infile) {
    const std::string suffixFree = infile.substr(0, infile.find_last_of('.'));
    const size_t lastSlash = suffixFree.find_last_of('/');
    const std::string prefixFree = (lastSlash != std::string::npos) ? suffixFree.substr(lastSlash+1) : suffixFree;

    return "out/" + prefixFree + "/";
}

void process(const std::string & infile, const std::vector<Mask> & masks) {
    auto img = loadImage(infile);
    const auto outPath = formOutPath(infile);
    std::cout << outPath << std::endl;
    fs::recreateDir(outPath);

    std::vector<std::thread> threads;

    for (const Mask & mask : masks) {
        std::thread t {
            [&]() -> void {
                const auto newImage = img * mask;
                newImage.saveToFile(outPath + mask.name() + ".png");
            }
        };
        threads.emplace_back(std::move(t));
    }

    std::for_each(threads.begin(), threads.end(), [](std::thread & t) { t.join(); });
}

void log(const FileNotFoundException & e) {
    std::cout << e.what() << std::endl;
}

void log(const std::exception & e) {
    std::cout << e.what() << std::endl;
    std::cout << "Unexpected error..." << std::endl;
}


int main(int argc, const char * argv[]) {
    fs::mkdir("out/");
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

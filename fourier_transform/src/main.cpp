#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "matrix.hpp"
#include "fs.hpp"
#include "util.hpp"
#include "fft.hpp"
#include "img_transform.hpp"


std::string folderName(std::string imgName) {
    const auto lastSlash = imgName.find_last_of('/');

    if (lastSlash != std::string::npos) {
        imgName = imgName.substr(lastSlash);
    }

    const auto lastPeriod = imgName.find_last_of('.');

    if (lastPeriod != std::string::npos) {
        imgName = imgName.substr(0, lastPeriod);
    }

    return imgName;
}

void transformImage(const std::string & filename, const bool printMask) {
    fs::mkdir("out/");

    const auto folder = "out/" + folderName(filename) + "/";
    fs::recreateDir(folder);

    auto f = fft::fft(loadImage(filename));

    std::cout << "Processing " << filename << "..." << std::endl;

    auto power = powerSpectrum(f);
    auto powerImg = powerSpectrumToImg(power);
    powerImg.saveToFile(folder + "power.png");

    auto phase = phaseShift(f);
    auto phaseImg = phaseShiftToImg(phase);
    phaseImg.saveToFile(folder + "phase.png");

    auto f90 = f.applyMask(circleMask(f, 0.1));
    fft::ifft(f90).saveToFile(folder + "90pct.png");
    auto f85 = f.applyMask(circleMask(f, 0.15));
    fft::ifft(f85).saveToFile(folder + "85pct.png");
    auto f80 = f.applyMask(circleMask(f, 0.20));
    fft::ifft(f80).saveToFile(folder + "80pct.png");
    auto f75 = f.applyMask(circleMask(f, 0.25));
    fft::ifft(f75).saveToFile(folder + "75pct.png");
    auto f50 = f.applyMask(circleMask(f, 0.50));
    fft::ifft(f50).saveToFile(folder + "50pct.png");
    auto f25 = f.applyMask(circleMask(f, 0.75));
    fft::ifft(f25).saveToFile(folder + "25pct.png");

    if (printMask) {
        std::cout << circleMask(f, 0.50) << std::endl;
    }

    auto invFourier = fft::ifft(f);
    invFourier.saveToFile(folder + "inverse_fourier.png");
}

int main(int argc, const char * argv[]) {

    std::vector<std::string> filenames;
    bool printMask = false;

    for (int i = 1; i < argc; ++i) {
        std::string str = argv[i];
        if (str == "-p" or str == "--print-mask") {
            printMask = true;
        } else {
            filenames.emplace_back(std::move(str));
        }
    }

    auto fun = [printMask](const std::string & filename) -> void { transformImage(filename, printMask); };
    std::for_each(filenames.begin(), filenames.end(), fun);
}

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "image_rotation.hpp"
#include "image_scaling.hpp"


int main(int argc, const char * argv[]) {
    sf::Image lena;
    lena.loadFromFile("resources/lena64.png");

    const auto s12 = scale(lena, 1.2);
    s12.saveToFile("s12.png");
    const auto s12_lin = scale(lena, 1.2, bilinearInterpolation);
    s12_lin.saveToFile("s12_lin.png");
    const auto s15 = scale(lena, 1.5);
    s15.saveToFile("s15.png");
    const auto s15_lin = scale(lena, 1.5, bilinearInterpolation);
    s15_lin.saveToFile("s15_lin.png");
    const auto s17 = scale(lena, 1.7);
    s17.saveToFile("s17.png");
    const auto s17_lin = scale(lena, 1.7, bilinearInterpolation);
    s17_lin.saveToFile("s17_lin.png");
    const auto s2 = scale(lena, 2);
    s2.saveToFile("s2.png");
    const auto s2_lin = scale(lena, 2, bilinearInterpolation);
    s2_lin.saveToFile("s2_lin.png");

    const auto pi2 = rotate(lena, M_PI * 0.5);
    pi2.saveToFile("pi2.png");
    const auto pi4 = rotate(lena, M_PI * 0.25);
    pi4.saveToFile("pi4.png");
    const auto pi3 = rotate(lena, M_PI * 0.33);
    pi3.saveToFile("pi3.png");

    // const auto throwaway = rotate(lena, M_PI * 0.5, bicubicInterpolation);

    const auto bi_pi2 = rotate(lena, M_PI * 0.5, bilinearInterpolation);
    bi_pi2.saveToFile("bi_pi2.png");
    const auto bi_pi4 = rotate(lena, M_PI * 0.25, bilinearInterpolation);
    bi_pi4.saveToFile("bi_pi4.png");
    const auto bi_pi3 = rotate(lena, M_PI * 0.33, bilinearInterpolation);
    bi_pi3.saveToFile("bi_pi3.png");
    const auto bi_pi13 = rotate(lena, M_PI * 1.33, bilinearInterpolation);
    bi_pi13.saveToFile("bi_pi13.png");
}

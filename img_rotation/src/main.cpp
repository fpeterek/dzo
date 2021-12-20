#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "image_rotation.hpp"


int main(int argc, const char * argv[]) {
    sf::Image lena;
    lena.loadFromFile("resources/lena64.png");
    const auto pi2 = rotate(lena, M_PI * 0.5);
    pi2.saveToFile("pi2.png");
    const auto pi4 = rotate(lena, M_PI * 0.25);
    pi4.saveToFile("pi4.png");
    const auto pi3 = rotate(lena, M_PI * 0.33);
    pi3.saveToFile("pi3.png");


    const auto bi_pi2 = rotate(lena, M_PI * 0.5, bilinearInterpolation);
    bi_pi2.saveToFile("bi_pi2.png");
    const auto bi_pi4 = rotate(lena, M_PI * 0.25, bilinearInterpolation);
    bi_pi4.saveToFile("bi_pi4.png");
    const auto bi_pi3 = rotate(lena, M_PI * 0.33, bilinearInterpolation);
    bi_pi3.saveToFile("bi_pi3.png");
    const auto bi_pi13 = rotate(lena, M_PI * 1.33, bilinearInterpolation);
    bi_pi13.saveToFile("bi_pi13.png");
}

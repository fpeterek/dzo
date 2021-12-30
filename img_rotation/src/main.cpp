#include <cmath>

#include <SFML/Graphics.hpp>

#include "image_rotation.hpp"
#include "image_scaling.hpp"
#include "distortion_correction.hpp"
#include "util.hpp"


int main(int, const char **) {

    sf::Image pano = loadImage("resources/distorted_panorama.jpg");
    removeDistortion(pano, 0.06, 0.01).saveToFile("panorama.png");

    sf::Image window = loadImage("resources/distorted_window.jpg");
    removeDistortion(window, 0.17, 0.06).saveToFile("window.png");

    sf::Image lena = loadImage("resources/lena64.png");

    scale(lena, 1.2).saveToFile("s12.png");
    scale(lena, 1.2, bilinearInterpolation).saveToFile("s12_lin.png");
    scale(lena, 1.5).saveToFile("s15.png");
    scale(lena, 1.5, bilinearInterpolation).saveToFile("s15_lin.png");
    scale(lena, 1.7).saveToFile("s17.png");
    scale(lena, 1.7, bilinearInterpolation).saveToFile("s17_lin.png");
    scale(lena, 2).saveToFile("s2.png");
    scale(lena, 2, bilinearInterpolation).saveToFile("s2_lin.png");

    rotate(lena, M_PI * 0.5).saveToFile("pi2.png");
    rotate(lena, M_PI * 0.25).saveToFile("pi4.png");
    rotate(lena, M_PI * 0.33).saveToFile("pi3.png");

    rotate(lena, M_PI * 0.5, bilinearInterpolation).saveToFile("pi2_lin.png");
    rotate(lena, M_PI * 0.25, bilinearInterpolation).saveToFile("pi4_lin.png");
    rotate(lena, M_PI * 0.33, bilinearInterpolation).saveToFile("pi3_lin.png");
    rotate(lena, M_PI * 1.33, bilinearInterpolation).saveToFile("pi13_lin.png");
}

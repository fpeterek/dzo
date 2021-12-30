# Image Rotation, Image Scaling, Distortion Correction

This project was initially supposed to only contain the logic
for image rotation and scaling, but as distortion correction
also requires some form of interpolation, and as I already
had bilinear interpolation implemented, I made the decision
to include distortion correction in this project as well.

## Code Description

### `image_scaling.hpp`/`image_scaling.cpp`

This pair of files contains the declaration/implementation
of the `scale` function, which scales an image by a certain factor.
The input image, the scale factor, as well as the pixel approximation
function may be passed in as function arguments.

### `image_rotation.hpp`/`image_rotation.cpp`

These two files implement the `rotate` functions, which rotates
the input image by the input angle using the input pixel approximation
function. Other than that, helper functions and structures are included
as well. These helper utilities provide the functionality to calculate
dimensions of the output image such that the output image can contain
the entirety of the rotated input image, or the functionality to
rotate a pixel around a pivot.

### `distortion_correction.hpp`/`distortion_correction.cpp`

The `distortion_correction.hpp` file only declares one function,
`sf::Image removeDistortion(const sf::Image & img, double coeff1, double coeff2)`.
This function attempts to correct distortion. The arguments, `coeff1` and `coeff2`,
are used as the coefficients for the Taylor polynomial used to correct distortion.
Unfortunately, this implementation does not include a fancy OpenCV slider, and the
coefficients used in the `main` function when invoking `removeDistortion` are likely
suboptimal.

### `pixel_approximation.hpp`/`pixel_approximation.cpp`

This file pair contains declaration/implementation of
the nearest neighbour and bilinear interpolation techniques
of approximating the value of a pixel.

### `util.hpp`/`util.cpp`

The `util.hpp`/`util.cpp` file pair contains certain utility
functions, such as `operator<<` overloads used to output a
vector to an output stream, functions to work with angles and
distances, functions to work with images and colors, etc.

### `main.cpp`

The `main.cpp` file only contains the `int main(int, const char**)`
function, which only calls the functions which perform scaling,
rotation and distortion correction.

## Sample inputs/outputs

To emphasize the importance of consistency, the input files
are inconsistently located inside the `resources/` folder.
The output files are, ingeniously, located inside the `sample_out/`
folder.

# Fourier Transform

## Code Description

### `util.hpp`/`util.cpp`

Contains utility functions, such as a function to load an image
or a function which splits an `std::vector` into two vectors
containing even and odd items respectively.

### `fs.hpp`/`fs.cpp`

Filesystem utility functions which make working with the filesystem
a bit easier.

### `matrix.hpp`

A Matrix class used to represent a 2D matrix. This class is then
used to represent the result of application of the Fourier transform
(i.e. images represented in the frequency domain) as well as filters,
which can be applied to filter out certain frequencies.


### `sft.hpp`/`sft.cpp`

Slow Fourier Transform - O(n^4) implementation of Fourier transform
and inverse Fourier transform.


### `fft.hpp`/`fft.cpp`

Fast Fourier Transform - a much faster, O(n^2 * log(n)) implementation
of Fourier transform and its inverse counterpart.

### `img_transform.hpp`/`img_transform.cpp`

Contains functions which compute the phase shift and the power spectrum
of images, as well as functions capable of converting such data to images
so that we can display the phase shift/power spectrum.

### `main.cpp`

Parses command line arguments, applies Fourier transform on each input file,
computes the power spectrum and phase shift, applies multiple filters on the
input image to filter out high frequencies, applies the inverse Fourier
transform on each filtered image to reconstruct the image and stores all the
results inside the `out/` folder.

## Input

Sample input images are located inside the [`in/`](in/) folder.

## Output

The results of applying the algorithm to the input images can be
found in the [`out/`](out/) folder.

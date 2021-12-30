# Digital Image Processing

Solutions to Digital Image Processing assignments.

This repository contains C++ implementations of

* [Convolution](convolution/)
* [Fourier Transform](fourier_transform/)
* [Image Rotation, Image Scaling, Distortion Correction](img_rotation/)

Each folder contains a description of the code as well as sample
inputs and outputs.

## Build

```sh
cmake . -DCMAKE_BUILD_TYPE=Release
make
```

Requires SFML, cmake, make, and a modern version of G++ to
be installed.

To install SFML, run

```sh
sudo pacman -S sfml
```
 
or, if you're running a Debian based distro

```sh
sudo apt install libsfml-dev
```

## Run

```sh
./convolution in/*
```

```sh
./fourier in/*
```

```sh
./img_rotation
```


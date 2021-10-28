# Digital Image Processing

Solutions to Digital Image Processing assignments.

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


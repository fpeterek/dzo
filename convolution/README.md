# Convolution

## Code Description

### `convolution_operator.hpp`/`convolution_operator.cpp`

`convolution_operator.hpp`/`convolution_operator.cpp` files
contain implementation of the `ConvolutionOperator` class.
This class simply realizes the application of convolution
using a mask on an input image.

The vast bulk of the work is done by the 
`void ConvolutionOperator::applyToPixel(size_t, size_t)`
member function, which applies the mask to the target pixels and its
surroundings, sums up the result and stores the resulting pixel
in the destination image.

An `operator*` overload is provided, mostly to serve as syntactic sugar.
This operator accepts a `const sf::Image &` as its first parameter,
a `const Mask &` as its second parameter, constructs the `ConvolutionOperator`
object, applies the mask onto the image and returns the result.

### `mask.hpp`/`mask.cpp`

This pair of files contains the definition and implementation of the `Mask`
class. This class serves mostly as a wrapper over a vector of vectors of
floats, i.e. a 2D matrix. `Mask` objects store a matrix of weights used
when applying convolution.

### `main.cpp`

The `main.cpp` file only contains a couple of helper functions used to
load all the necessary input files, log errors, etc. Besides that, the logic
found inside the `main.cpp` file just applies every mask found in the `masks/`
folder on every input file passed as a command line argument and stores
the result inside the `out/` folder.

### `fs.hpp`/`fs.cpp`

The `fs.cpp` file only contains a couple filesystem utilities
which make working with the filesystem a bit easier.

The `fs.hpp` header file, unsurprisingly, only contains declarations
for said utility functions.

### `file_not_found.hpp`/`file_not_found.cpp`

This header file/source file pair only contains a single exception
used to denote the exceptional state when a file specified by the
user could not be found.

## Input

Sample input files can be located inside the [`in/`](in/) folder.

Sample masks can be found inside the [`masks/`](masks/) folder.

## Output

The result of applying the sample masks on the sample images can be
found inside the [`out/`](out/) folder.

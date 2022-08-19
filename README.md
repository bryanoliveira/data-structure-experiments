# Hashmap Experiments

Implements a generic hashmap that uses quadratic probing by default. It also supports linear probing by setting the `LINEAR_PROBING=1` compiler flag.

## Requirements

To build this program from source you'll need g++ (C++ 17), _make_ and the Boost program_options module.

You can probably install them all using `sudo apt install build-essential libboost-all-dev`. 

### Development

For development, clang-format is recommended. You can install it with `sudo apt install clang-format`
You should also use the [Clang-Format VSCode Extension](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) when using `clang-format`.

## Usage

### Building From Source

- Install the requirements
- Clone this repository
- Building and executing:
  - Run `make` to build and run
  - Run `make LINEAR_PROBING=1` to build and run using linear probing (instead of quadratic)
  - Run `make hashmap` to build
  - Run `make run` to run with default parameters
  - Run `make clean` to remove generated files
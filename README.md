# Game title

A 2D proof-of-concept game

## Requirements

- CMake
- Ninja build system
- Clang compiler

## Set up

### Clone the repo
```sh
git clone --recurse-submodules git@github.com:kipiiler/POC.git
cd POC
```

### Build the targets using CMake
```sh
cmake --preset base
cmake --build --preset simple-all
```

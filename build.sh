#!/bin/sh

set -xe

# Compiling Raylib
cd raylib/raylib-5.0/src
make PLATFORM=PLATFORM_DESKTOP
cd -

# Copy raylib library in build folder
cp ./raylib/raylib-5.0/src/raylib.h ./build/
cp ./raylib/raylib-5.0/src/libraylib.a ./build/

# Create the build folder
mkdir -p build/

# Compiler options
COMPILER="clang" # or gcc (both works)
CFLAGS="-Wall -Wextra"
# CINCLUDE="-I./raylib/raylib-5.0/src"
CINCLUDE="-I./build/"
# CLINK="-L./raylib/raylib-5.0/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
CLINK="-L./build/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
DEBUG="-g"

$COMPILER $DEBUG $CFLAGS -o build/raypong src/*.c $CINCLUDE $CLINK

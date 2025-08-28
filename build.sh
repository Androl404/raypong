#!/bin/sh

set -xe

# Create the build folder
mkdir -p build/

if ! test -e ./build/libraylib.a
then
    # Compiling Raylib
    mkdir -p raylib/build/
    cd raylib/build/
    cmake -DCUSTOMIZE_BUILD=ON -DBUILD_EXAMPLES=OFF ..
    make PLATFORM=PLATFORM_DESKTOP
    cd -
fi

# Create raylib symlink in build folder
if ! test -e ./build/raylib.h
then
    ln -sf ../raylib/build/raylib/include/raylib.h build/
fi

if ! test -e ./build/libraylib.a 
then
    ln -sf ../raylib/build/raylib/libraylib.a build/
fi

# Compiler options
COMPILER="cc" # or gcc (both works)
CFLAGS="-Wall -Wextra"
# CINCLUDE="-I./raylib/raylib-5.0/src"
CINCLUDE="-I./build/"
# CLINK="-L./raylib/raylib-5.0/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
CLINK="-L./build/ -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
DEBUG="-g"

$COMPILER $DEBUG $CFLAGS -o build/raypong src/*.c $CINCLUDE $CLINK

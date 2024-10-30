#!/bin/sh

set -xe

# Create the build folder
mkdir -p build/

if ! test -e ./raylib/raylib-5.0/src/libraylib.a
then
    # Compiling Raylib
    cd raylib/raylib-5.0/src
    make PLATFORM=PLATFORM_DESKTOP
    cd -
fi

# Create raylib symlink in build folder
if ! test -e ./build/raylib.h
then
    ln -s ../raylib/raylib-5.0/src/raylib.h build/
fi

if ! test -e ./build/libraylib.a 
then
    ln -s ../raylib/raylib-5.0/src/libraylib.a build/
fi

# Compiler options
COMPILER="clang" # or gcc (both works)
CFLAGS="-Wall -Wextra"
# CINCLUDE="-I./raylib/raylib-5.0/src"
CINCLUDE="-I./build/"
# CLINK="-L./raylib/raylib-5.0/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
CLINK="-L./build/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
DEBUG="-g"

$COMPILER $DEBUG $CFLAGS -o build/raypong src/*.c $CINCLUDE $CLINK

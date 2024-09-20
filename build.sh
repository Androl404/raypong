#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"
CINCLUDE="-I./raylib/raylib-5.0/src"
CLINK="-L./raylib/raylib-5.0/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
DEBUG="-g"

clang $DEBUG $CFLAGS -o build/raypong src/*.c $CINCLUDE $CLINK

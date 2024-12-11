# Raypong

A simple ping-pong game written in C with the [Raylib](https://github.com/raysan5/raylib) Graphics library.

## Description

**Raypong** is a simple ping-pong game which allows two users to play a ping-pong game together, sharing the keyboard. The ball will be faster and faster and the user will need to be quick in order to win the game.

> [!WARNING] 
> **THIS SOFTWARE IS UNFINISHED AND IS NOT STABLE. USE IT CAREFULLY!!! The author is not responsible for anything that might happen to you and your system!**

### Key-bindings

Different key-bindings are available to move the two bars:
* Player 1 - Move up : UP key, 
* Player 1 - Move down : DOWN key,
* Player 2 - Move up : J key (like in the Vim editor),
* Player 2 - Move down : K key (like in the Vim editor).

### Screenshots

*Coming soon... (when the game logic will be fully implemeted)*

## Build the project

This project can be build with the script `build.sh`. We use the `clang` compiler so make sure it is in your path. The game can also be build with the GNU compiler (`gcc`), it also works (you can change in the `build.sh` file).

Some dependencies are required in order to build this project, `raylib` is included in the repo, but you will also need the libraries `GL` (OpenGL), `m`, `pthread` (for multithreading), `dl`, `rt` and `X11`. Use your packet manager to install these libraries.

```console
$ ./build.sh # To build the project
$ ./build/raypong # To launch the game
```

*When the game will be in a releasable state, we plan to also compile it to WebAssembly so the users will be able to play the game in the browser.*

## Contribution
 
You are free to fork this project and contribute to it (only if you want to) by making a pull request or oppening and issue. Please add some details with the modification you are pushing if you are making a pull request or describe what went wrong if you are opening an issue.

## Licence

This project is licenced beyond the `MIT` licence. You are free to do whatever you want with this project. The author can not be responsible for anything that happer to your system.

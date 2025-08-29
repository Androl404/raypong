#include <raylib.h>
#include <stddef.h>

#include "state.h"

#define WINDOW_SIZE_FACTOR 80

int main(void) {
    // SetTraceLogLevel(LOG_ERROR);

    // To make the window resizeable
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(WINDOW_SIZE_FACTOR*16, WINDOW_SIZE_FACTOR*9, "Raypong - Ping-pong in C!");
    SetWindowMinSize(800, 600);
    SetTargetFPS(60);

    Smain smain = State_init();
    while (!WindowShouldClose()) {
        State_update(&smain);
    }
    State_destroy(&smain);
    CloseWindow();

    return 0;
}

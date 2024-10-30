#include <stdio.h>
#include <raylib.h>

#include "state.h"

int main(void) {
    // To make the window resizeable
    /* SetTraceLogLevel(LOG_ERROR);  */
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    const size_t factor = 80;
    InitWindow(factor*16, factor*9, "Raypong - Ping-pong in C!");
    SetTargetFPS(60);

    /* OpenSans = LoadFont("/usr/share/fonts/IosevkaNerdFont-Regular.ttf"); */
    /* SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_ANISOTROPIC_4X); */

    Smain smain = State_init();
    while (!WindowShouldClose()) {
	State_update(&smain);
    }
    State_destroy(&smain);
    CloseWindow();
    
    return 0;
}

#include <raylib.h>

#include "button.h"

// Stolen code: https://github.com/lemonzninja/Raylib-Make-A-Button

// Function to check if the mouse is over the button
bool is_mouse_over_button(Button button) {
    /*
        This function will check if the mouse is over the button
        button: the button to check
    */

    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}


#include <raylib.h>
#include <stddef.h>

#include "state.h"
#include "button.h"

// Stolen code: https://github.com/lemonzninja/Raylib-Make-A-Button
/*
 * Verifies if the cursor is over a button
 * Take a Button as argument
 * Returns a boolean
 */
bool Is_mouse_over_button(Button button) {
    /*
        This function will check if the mouse is over the button
        button: the button to check
    */
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

/*
 * Calculate and modifies the rectangle for the button
 * Take a pointer to a Button as argument
 * Does not return anything
 */
void Calculate_button_rectangle(Button* button) {
    button->rect.width = MeasureTextEx(button->text.font, button->text.text, button->text.text_size, 2).x + 2 * button->padding.x;
    button->rect.height = MeasureTextEx(button->text.font, button->text.text, button->text.text_size, 2).y + 2 * button->padding.y;
    button->rect.x = button->position.x - button->rect.width / 2;
    button->rect.y = button->position.y - button->rect.height / 2;
}

/*
 * Draws the button (rectangle + text) at the correct position
 * Take a Button as argument (read-only)
 * Returns a boolean
 */
void Draw_button(const Button button) {
    Vector2 position = {
    button.position.x - MeasureTextEx(button.text.font, button.text.text, button.text.text_size, 2).x / 2,
    button.position.y - MeasureTextEx(button.text.font, button.text.text, button.text.text_size, 2).y / 2,
    };
    DrawRectangleRec(button.rect, button.background_color);
    DrawTextEx(button.text.font, button.text.text, position, button.text.text_size, 2, button.text.text_color);
}

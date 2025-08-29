#ifndef BUTTON_H
#define BUTTON_H

// A struct to hold the button data
typedef struct Button {
    Color background_color;
    Text text;
    Vector2 position;
    Vector2 padding;
    Rectangle rect;
} Button;

/*
 * Verifies if the cursor is over a button
 * Take a Button as argument
 * Returns a boolean
 */
bool Is_mouse_over_button(Button button);

/*
 * Calculate and modifies the rectangle for the button
 * Take a pointer to a Button as argument
 * Does not return anything
 */
void Calculate_button_rectangle(Button* button);

/*
 * Draws the button (rectangle + text) at the correct position
 * Take a Button as argument (read-only)
 * Returns a boolean
 */
void Draw_button(const Button button);

#endif // BUTTON_H

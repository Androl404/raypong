// A struct to hold the button data
typedef struct Button {
    Rectangle rect;
    Color color;
} Button;

/* void init_button(Button *button, Rectangle rect, Color color); */

/*
 * Verifies if the cursor is over a button
 * Take a Button as argument
 * Returns a boolen
 */
bool is_mouse_over_button(Button button);


#include <raylib.h>

#include "state.h"
#include "button.h"

Smain smain;

/*
 * Initiate the game
 * Does not take any argument
 * Returns a pointer to the main struct (Smain)
 */
Smain* state_init(void) {
    Smain* smain_ptr = &smain;
    smain_ptr->OpenSans = LoadFont("./assets/fonts/Open_Sans/OpenSans-Regular.ttf");
    smain_ptr->state = 0;
    return smain_ptr;
}

/*
 * Updates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void state_update(Smain* smain) {
    if (smain->state == 0) {
	welcome_frame(smain);
    } else if (smain->state == 1) {
	game_frame(smain);
    }
}

/*
 * Create the welcome frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void welcome_frame(Smain* smain) { 
    Vector2 center, text_measure;
    const char home_text[] = "Congrats! You created your first window!";
	
    center.x = (float) (GetScreenWidth()/2);
    center.y = (float) (GetScreenHeight()/2);
    text_measure = MeasureTextEx(smain->OpenSans, home_text, 60, 2);
    center.x -= text_measure.x/2;
    center.y -= text_measure.y/2;
	
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);
    DrawTextEx(smain->OpenSans, home_text, center, 60, 2, WHITE);
    center.x = (float) (GetScreenWidth()/2);
    center.y = (float) (GetScreenHeight()/2);
    Button play = {
	(Rectangle){center.x - 100, center.y - 50 + 150, 200, 100},
	RED,
    };
    if (is_mouse_over_button(play)) {
	play.color = BLUE;
    }
    // Change the screen collor when the button is clicked
    if (is_mouse_over_button(play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
	smain->state = 1;
    }
    DrawRectangleRec(play.rect, play.color);
    DrawTextEx(smain->OpenSans, "Click Me", (Vector2){play.rect.x + play.rect.width / 2 - MeasureText("Click Me", 20) / 2, play.rect.y + play.rect.height / 2 - 20 / 2}, 20, 2, WHITE);
    EndDrawing();
}

/*
 * Create and update the game frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void game_frame(Smain* smain) {
    smain->state = 0;
}

/*
 * Terminates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void state_destroy(Smain* smain) {
    UnloadFont(smain->OpenSans);
}

#include <raylib.h>
#include <stddef.h>

#include "state.h"
#include "button.h"

/*
 * Initiate the game
 * Does not take any argument
 * Returns a main struct (Smain)
 */
Smain State_init(void) {
    Smain smain = {
	LoadFontEx("./assets/fonts/Alegreya/Alegreya-Regular.ttf", 64, 0, 0),
	0,
	{
	    {
		0,
		0,
		GAME_BAR_WIDTH,
		100,
	    },
	    {
		GetScreenWidth() - 9,
		0,
		GAME_BAR_WIDTH,
		100,
	    },
	},
    };
    return smain;
}

/*
 * Updates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void State_update(Smain* smain) {
    if (smain->state == 0) {
	Welcome_frame(smain);
    } else if (smain->state == 1) {
	Game_frame(smain);
    }
}

/*
 * Create the welcome frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void Welcome_frame(Smain* smain) {
    Vector2 center, text_measure, position;
    Text main_title = {
	"Raypong",
	smain->main_font,
	64,
	WHITE,
    };

    center.x = (float) (GetScreenWidth()/2);
    center.y = (float) (GetScreenHeight()/2);
    text_measure = MeasureTextEx(main_title.font, main_title.text, main_title.text_size, 2);
    position.x = center.x - text_measure.x / 2;
    position.y = center.y - text_measure.y / 2;

    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);
    DrawTextEx(main_title.font, main_title.text,position, main_title.text_size, 2, WHITE);

    Text button_text = {
	"Play",
	smain->main_font,
	50,
	WHITE,
    };
    Button play = {
	RED,
	button_text,
        {
	    center.x,
	    center.y + 100,
	},
	(Vector2) { 25, 5 },
    };

    Calculate_button_rectangle(&play);
    if (Is_mouse_over_button(play)) {
	play.background_color = BLUE;
    }
    // Change the screen collor when the button is clicked
    if (Is_mouse_over_button(play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
	smain->state = 1;
    }

    Draw_button(play);
    EndDrawing();
}

/*
 * Create and update the game frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void Game_frame(Smain* smain) {
    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);
    smain->main_structure.bar2.x = GetScreenWidth() - GAME_BAR_WIDTH;

    const int keys1[] = { KEY_DOWN, KEY_UP };
    const int keys2[] = { KEY_J, KEY_K };
    
    Handle_bar_moves(&smain->main_structure.bar1, keys1);
    Handle_bar_moves(&smain->main_structure.bar2, keys2);
    
    Render_game_elements(smain->main_structure);
    EndDrawing();
}

/*
 * Adapts the bar position acoordingly to the user input
 * Takes a pointer to a rectangle representing one bar and a list with the two keys which can be pressed as arguments
 * Does not return anything
 */
void Handle_bar_moves(Rectangle* bar, const int keys[]) {
    const size_t speed = 3;
    if (IsKeyDown(keys[0]) || bar->y > GetScreenHeight() - 100) {
	if (bar->y >= GetScreenHeight() - 100) {
	    bar->y = GetScreenHeight() - 100;
	} else {
	    bar->y += speed;
	}
    } else if (IsKeyDown(keys[1])) {
	if (bar->y <= 0) {
	    bar->y = 0;
	} else {
	    bar->y -= speed;
	}
    }
}

/*
 * Renders all the elements of the main game
 * Takes a game structure as argument
 * Does not return anything
 */
void Render_game_elements(const Game_structure structure) {
    DrawRectangleRec(structure.bar1, BLUE);
    DrawRectangleRec(structure.bar2, RED);
}

/*
 * Terminates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void State_destroy(Smain* smain) {
    UnloadFont(smain->main_font);
}

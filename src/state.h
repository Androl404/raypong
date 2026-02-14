#ifndef STATE_H
#define STATE_H

#include <stdint.h>

// Definitions
#define COLOR_BACKGROUND GetColor(0x151515FF)
#define DARKRED CLITERAL(Color){ 200, 41, 55, 255 }
#define GAME_BAR_WIDTH 14
#define GAME_BAR_HEIGHT 100

// Enumeration for the actual state of the game
enum Game_state {
    WELCOME_FRAME = 0,
    GAME_FRAME = 1,
    LOST_FRAME = 2,
};

enum Ball_hitting_points {
    LEFT_SIDE = 0,
    RIGHT_SIDE = 1,
};

// Structure for the ball
typedef struct Ball {
    size_t radius;
    size_t speed;
    Vector2 position;
    Vector2 speed_vector;
    enum Ball_hitting_points should_hit;
} Ball;

// Main game structure with all the elements of the game
typedef struct Game_structure {
    Rectangle bar1;
    Rectangle bar2;
    Ball ball;
} Game_structure;

// Structure with content for the main game
typedef struct Smain {
    Font main_font;
    enum Game_state state;
    Game_structure main_structure;
    int64_t score;
} Smain;

// Structure to hold all of the text information
typedef struct Text {
    const char* text;
    Font font;
    size_t text_size;
    Color text_color;
} Text;

/*
 * Initiate the game
 * Does not take any argument
 * Returns a main struct (Smain)
 */
Smain State_init(void);

/*
 * Updates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void State_update(Smain* smain);

/*
 * Create the welcome frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void Welcome_frame(Smain* smain);

/*
 * Create and update the game frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void Game_frame(Smain* smain);

/*
 * Renders the "lost" frame, displaying the score to the user, and allowing him to replay.
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void Lost_frame(Smain *smain);

/*
 * Terminates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void State_destroy(Smain* smain);

/*
 * Renders all the elements of the main game
 * Takes a game structure as argument
 * Does not return anything
 */
void Render_game_elements(const Smain game_structure);

/*
 * Adapts the bar position acoordingly to the cursor position on the screen
 * Takes a pointer to a rectangle representing one bar
 * Does not return anything
 */
void Handle_bar_mouse_movement(Rectangle *bar);

/*
 * Adapts the ball position acoordingly to its speed vector
 * Takes a pointer to the ball as argument
 * Does not return anything
 */
void Update_ball_position(Game_structure *game, int64_t *score, enum Game_state *game_status);

#endif // STATE_H

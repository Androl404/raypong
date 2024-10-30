#define COLOR_BACKGROUND GetColor(0x151515FF)
#define GAME_BAR_WIDTH 10

// Structure for the ball
typedef struct Ball {
    float radius;
    size_t speed;
    Vector2 position;
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
    int state;
    Game_structure main_structure;
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
void Render_game_elements(const Game_structure structure);

/*
 * Adapts the bar position acoordingly to the user input
 * Takes a pointer to a rectangle representing one bar and a list with the two keys which can be pressed as arguments
 * Does not return anything
 */
void Handle_bar_moves(Rectangle* bar, const int keys[]);

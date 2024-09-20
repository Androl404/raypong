#define COLOR_BACKGROUND GetColor(0x151515FF)

/*
 * Structure with content for the main game
 */
typedef struct Smain {
    Font OpenSans;
    int state;
} Smain;

/*
 * Initiate the game
 * Does not take any argument
 * Returns a pointer to the main struct (Smain)
 */
Smain* state_init(void);

/*
 * Updates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void state_update(Smain* smain);

/*
 * Create the welcome frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void welcome_frame(Smain* smain);

/*
 * Create and update the game frame
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void game_frame(Smain* smain);

/*
 * Terminates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void state_destroy(Smain* smain);

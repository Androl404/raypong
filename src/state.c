#include <raylib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

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
        WELCOME_FRAME,
        {
            {
                0,
                0,
                GAME_BAR_WIDTH,
                GAME_BAR_HEIGHT
            },
            {
                GetScreenWidth() - GAME_BAR_WIDTH,
                0,
                GAME_BAR_WIDTH,
                GAME_BAR_HEIGHT,
            },
            {
                20,
                5,
                {
                    GetScreenWidth() / 2.0,
                    GetScreenHeight() / 2.0,
                },
                {
                    2,
                    2,
                },
                RIGHT_SIDE,
            },
        },
        0,
    };
    return smain;
}

/*
 * Updates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void State_update(Smain *smain) {
    if (smain->state == WELCOME_FRAME) {
        Welcome_frame(smain);
    } else if (smain->state == GAME_FRAME) {
        Game_frame(smain);
    } else if (smain->state == LOST_FRAME) {
        Lost_frame(smain);
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

    center.x = GetScreenWidth() / 2.0;
    center.y = GetScreenHeight() / 2.0;
    text_measure = MeasureTextEx(main_title.font, main_title.text, main_title.text_size, 2);
    position.x = center.x - text_measure.x / 2;
    position.y = center.y - text_measure.y / 2 - 20;

    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);
    DrawTextEx(main_title.font, main_title.text, position, main_title.text_size, 2, WHITE);

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
            center.y + 45,
        },
        (Vector2){30, 0},
        (Rectangle){0},
    };

    Calculate_button_rectangle(&play);
    if (Is_mouse_over_button(play)) {
        play.background_color = DARKRED;
    }
    // Change the screen collor when the button is clicked
    if (Is_mouse_over_button(play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        smain->state = GAME_FRAME;
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

    if (smain->main_structure.ball.should_hit == LEFT_SIDE)
        Handle_bar_mouse_movement(&smain->main_structure.bar1);
    else
        Handle_bar_mouse_movement(&smain->main_structure.bar2);

    Update_ball_position(&smain->main_structure, &smain->score, &smain->state);

    Render_game_elements(*smain);
    EndDrawing();
}

/*
 * Renders the "lost" frame, displaying the score to the user, and allowing him to replay.
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void Lost_frame(Smain *smain) {
    Vector2 center, text_measure, position;
    char text[30];
    sprintf(text, "You lost! Score: %zu", smain->score);
    Text main_title = {
        text,
        smain->main_font,
        64,
        WHITE,
    };

    center.x = GetScreenWidth() / 2.0;
    center.y = GetScreenHeight() / 2.0;
    text_measure = MeasureTextEx(main_title.font, main_title.text, main_title.text_size, 2);
    position.x = center.x - text_measure.x / 2;
    position.y = center.y - text_measure.y / 2 - 20;

    BeginDrawing();
    ClearBackground(COLOR_BACKGROUND);
    DrawTextEx(main_title.font, main_title.text, position, main_title.text_size, 2, WHITE);

    Text button_text = {
        "Play again",
        smain->main_font,
        50,
        WHITE,
    };
    Button play = {
        BLUE,
        button_text,
        {
            center.x,
            center.y + 45,
        },
        (Vector2){30, 0},
        (Rectangle){0},
    };

    Calculate_button_rectangle(&play);
    if (Is_mouse_over_button(play)) {
        play.background_color = DARKRED;
    }
    // Change the screen collor when the button is clicked
    if (Is_mouse_over_button(play) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        smain->score = 0;
        smain->state = GAME_FRAME;
        smain->main_structure.ball = (Ball){
            20,
            5,
            {
                GetScreenWidth() / 2.0,
                GetScreenHeight() / 2.0,
            },
            {
                2,
                2,
            },
            RIGHT_SIDE,
        };
    }

    Draw_button(play);
    EndDrawing();
}

/*
 * Adapts the bar position acoordingly to the cursor position on the screen
 * Takes a pointer to a rectangle representing one bar
 * Does not return anything
 */
void Handle_bar_mouse_movement(Rectangle *bar) {
    int mouse_position_y = GetMouseY();
    if (mouse_position_y > GetScreenHeight() - GAME_BAR_HEIGHT / 2.0) {
        bar->y = GetScreenHeight() - GAME_BAR_HEIGHT;
    } else if (mouse_position_y <= GAME_BAR_HEIGHT / 2.0) {
        bar->y = 0;
    } else {
        bar->y = mouse_position_y - (GAME_BAR_HEIGHT / 2.0);
    }
}

/*
 * Adapts the ball position acoordingly to its speed vector
 * Takes a pointer to the ball as argument
 * Does not return anything
 */
void Update_ball_position(Game_structure *game, int64_t *score, enum Game_state *game_status) {
    // Check for collision between ball and game rectangles
    bool collision_bar1 = CheckCollisionCircleRec(game->ball.position, game->ball.radius, game->bar1);
    bool collision_bar2 = CheckCollisionCircleRec(game->ball.position, game->ball.radius, game->bar2);

    // Check for collision with one of the game bars
    if (collision_bar1 && game->ball.should_hit == LEFT_SIDE) {
        game->ball.speed_vector.x *= -1;
        game->ball.should_hit = RIGHT_SIDE;
        *score += 1;
        game->ball.speed_vector.x += game->ball.speed_vector.x > 0 ? 0.7 : -0.7;
        game->ball.speed_vector.y += game->ball.speed_vector.y > 0 ? 0.7 : -0.7;
    } else if (collision_bar2 && game->ball.should_hit == RIGHT_SIDE) {
        game->ball.speed_vector.x *= -1;
        game->ball.should_hit = LEFT_SIDE;
        *score += 1;
        game->ball.speed_vector.x += game->ball.speed_vector.x > 0 ? 0.7 : -0.7;
        game->ball.speed_vector.y += game->ball.speed_vector.y > 0 ? 0.7 : -0.7;
    }

    // Check for windows size collision
    if ((game->ball.position.y + game->ball.radius) >= GetScreenHeight()) {
        // Bottom border
        game->ball.position.y = GetScreenHeight() - game->ball.radius - 1;
        game->ball.speed_vector.y *= -1;
    } else if ((game->ball.position.y - game->ball.radius) <= 0) {
        // Top border
        game->ball.speed_vector.y *= -1;
    } else if ((game->ball.position.x + game->ball.radius) >= GetScreenWidth()) {
        // Right border
        *game_status = LOST_FRAME;
    } else if ((game->ball.position.x - game->ball.radius) <= 0) {
        // Left border
        *game_status = LOST_FRAME;
    }

    // Update ball position
    game->ball.position.x += game->ball.speed_vector.x;
    game->ball.position.y += game->ball.speed_vector.y;
}

/*
 * Renders all the elements of the main game
 * Takes a game structure as argument
 * Does not return anything
 */
void Render_game_elements(const Smain game_structure) {
    DrawRectangleRec(game_structure.main_structure.bar1, BLUE);
    DrawRectangleRec(game_structure.main_structure.bar2, RED);
    DrawCircle(game_structure.main_structure.ball.position.x, game_structure.main_structure.ball.position.y, game_structure.main_structure.ball.radius, WHITE);
    char score_text[30];
    sprintf(score_text, "Score: %zu", game_structure.score);
    Text score = {
        (const char*)score_text,
        game_structure.main_font,
        64,
        WHITE,
    };
    DrawTextEx(score.font, score.text, (Vector2){ 50, 30 }, 64, 2, score.text_color);
}

/*
 * Terminates the game
 * Takes a pointer the main struct (Smain) as an argument
 * Does not return anything
 */
void State_destroy(Smain* smain) {
    UnloadFont(smain->main_font);
}

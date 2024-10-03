#include <raylib.h>

#define GAME_WIDTH 1280
#define GAME_HEIGHT 720

#define PLAYER_SPEED 300
#define PLAYER_SIDE 25

typedef struct Input {
    KeyboardKey up;
    KeyboardKey down;
    KeyboardKey left;
    KeyboardKey right;
} Input;

typedef struct Player {
    Vector2 pos;
    Input input;
} Player;

const Input INPUT_A = {.up = KEY_UP, .down = KEY_DOWN, .left = KEY_LEFT, .right = KEY_RIGHT};
const Input INPUT_B = {.up = KEY_W, .down = KEY_S, .left = KEY_A, .right = KEY_D};

const Input inputs[] = {
    INPUT_A,
    INPUT_B
};

void player_init(Player *p) {
    p->pos = {GAME_WIDTH / 2.f - PLAYER_SIDE / 2.f, GAME_HEIGHT / 2.f - PLAYER_SIDE / 2.f};
    p->input = inputs[0];
}

void player_switch_input(Player *p, unsigned int *input_idx) {
    *input_idx += 1;
    *input_idx = *input_idx % (sizeof(inputs) / sizeof(Input));
    p->input = inputs[*input_idx];
}

void player_move(Player *p) {
    float dt = GetFrameTime();

    if (IsKeyDown(p->input.up)) {
        p->pos.y -= PLAYER_SPEED * dt;
    }

    if (IsKeyDown(p->input.down)) {
        p->pos.y += PLAYER_SPEED * dt;
    }

    if (IsKeyDown(p->input.left)) {
        p->pos.x -= PLAYER_SPEED * dt;
    }

    if (IsKeyDown(p->input.right)) {
        p->pos.x += PLAYER_SPEED * dt;
    }
}

void player_draw(Player p) {
    DrawRectangle(p.pos.x, p.pos.y, PLAYER_SIDE, PLAYER_SIDE, RED);
}

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif

    InitWindow(GAME_WIDTH, GAME_HEIGHT, "command pattern lol");
    Player p;
    player_init(&p);
    unsigned int input_idx = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_C)) {
            player_switch_input(&p, &input_idx);
        }

        player_move(&p);

        BeginDrawing();
            ClearBackground(BLACK);
            int x = 0;

            const char *tip = "press 'C' to switch input (";
            DrawText(tip, x, 0, 24, RAYWHITE);
            x += MeasureText(tip, 24);

            const char *arrow_keys = "arrow keys";
            DrawText(arrow_keys, x, 0, 24, input_idx == 0 ? RED : RAYWHITE);
            x += MeasureText(arrow_keys, 24);

            const char *vs = " vs ";
            DrawText(vs, x, 0, 24, RAYWHITE);
            x += MeasureText(vs, 24);

            const char *wasd = "WASD";
            DrawText(wasd, x, 0, 24,  input_idx == 1 ? RED : RAYWHITE);
            x += MeasureText(wasd, 24);

            DrawText(")", x, 0, 24, RAYWHITE);

            player_draw(p);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

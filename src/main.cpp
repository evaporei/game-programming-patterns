#include <raylib.h>

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif

    InitWindow(800, 450, "game");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("game content here.", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

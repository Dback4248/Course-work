#include "game.h"
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Five Nights at Freddy's - Raylib Edition");
    InitAudioDevice();
    SetTargetFPS(60);

    Game game;
    game.Init();

    while (!WindowShouldClose())
    {
        game.Update();
        game.Draw();
    }

    game.Unload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

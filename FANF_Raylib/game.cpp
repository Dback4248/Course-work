#include "raylib.h"
#include "game.h"
void Game::Init()
{
    cameraSystem.Init();
    freddy.Init("assets/freddy.png");
    bonnie.Init("assets/bonnie.png");
    chica.Init("assets/chica.png");
    ui.Init();
}

void Game::Update()
{
    switch (state)
    {
    case STATE_MENU:
        if (IsKeyPressed(KEY_ENTER))
            state = STATE_PLAYING;
        break;

    case STATE_PLAYING:
        if (IsKeyPressed(KEY_A)) doorLeft = !doorLeft;
        if (IsKeyPressed(KEY_D)) doorRight = !doorRight;
        if (IsKeyPressed(KEY_S)) lightLeft = !lightLeft;
        if (IsKeyPressed(KEY_W)) lightRight = !lightRight;

        cameraSystem.Update();
        freddy.Update();
        bonnie.Update();
        chica.Update();

        power -= powerUsage;
        nightTime += GetFrameTime();

        if (power <= 0)
            state = STATE_JUMPSCARE;

        if (freddy.CheckJumpscare() || bonnie.CheckJumpscare() || chica.CheckJumpscare())
            state = STATE_JUMPSCARE;
        break;

    case STATE_JUMPSCARE:
        ui.PlayJumpscare();
        if (ui.IsJumpscareOver())
            state = STATE_GAMEOVER;
        break;

    case STATE_GAMEOVER:
        if (IsKeyPressed(KEY_ENTER))
        {
            power = 100;
            nightTime = 0;
            state = STATE_MENU;
        }
        break;
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (state)
    {
    case STATE_MENU:
        ui.DrawMenu();
        break;

    case STATE_PLAYING:
        cameraSystem.Draw();
        ui.DrawHUD(power, nightTime, doorLeft, doorRight, lightLeft, lightRight);
        break;

    case STATE_JUMPSCARE:
        ui.DrawJumpscare();
        break;

    case STATE_GAMEOVER:
        ui.DrawGameOver();
        break;
    }

    EndDrawing();
}

void Game::Unload()
{
    cameraSystem.Unload();
    freddy.Unload();
    bonnie.Unload();
    chica.Unload();
    ui.Unload();
}

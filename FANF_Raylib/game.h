#pragma once
#include "camera_system.h"
#include "animatronic.h"
#include "ui.h"
#include "raylib.h"

enum GameState
{
    STATE_MENU,
    STATE_PLAYING,
    STATE_JUMPSCARE,
    STATE_GAMEOVER
};

class Game
{
public:
    void Init();
    void Update();
    void Draw();
    void Unload();

private:
    GameState state = STATE_MENU;
    CameraSystem cameraSystem;
    Animatronic freddy, bonnie, chica;
    UI ui;

    float power = 100.0f;
    float powerUsage = 0.02f;
    float nightTime = 0.0f;
    bool doorLeft = false, doorRight = false;
    bool lightLeft = false, lightRight = false;
};

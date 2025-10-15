#pragma once
#include "raylib.h"

class UI
{
public:
    void Init();
    void DrawHUD(float power, float nightTime, bool dL, bool dR, bool lL, bool lR);
    void DrawMenu();
    void DrawJumpscare();
    void DrawGameOver();
    void PlayJumpscare();
    bool IsJumpscareOver();
    void Unload();

private:
    Texture2D jumpscareTex;
    Sound jumpscareSound;
    float jumpscareTimer = 0;
    bool playing = false;
};


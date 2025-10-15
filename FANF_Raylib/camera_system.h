#pragma once
#include "raylib.h"

class CameraSystem
{
public:
    void Init();
    void Update();
    void Draw();
    void Unload();

private:
    Texture2D cams[3];
    int currentCam = 0;
};


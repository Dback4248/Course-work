#include "camera_system.h"
#include "raylib.h"

void CameraSystem::Init()
{
    cams[0] = LoadTexture("assets/office.png");
    cams[1] = LoadTexture("assets/cam1.png");
    cams[2] = LoadTexture("assets/cam2.png");
}

void CameraSystem::Update()
{
    if (IsKeyPressed(MOUSE_LEFT_BUTTON)) currentCam = 0;
    if (IsKeyPressed(MOUSE_RIGHT_BUTTON)) currentCam = 1;
    if (IsKeyPressed(KEY_LEFT)) currentCam = 2;
}

void CameraSystem::Draw()
{
    DrawTexture(cams[currentCam], 0, 0, WHITE);
}

void CameraSystem::Unload()
{
    for (int i = 0; i < 3; i++) UnloadTexture(cams[i]);
}

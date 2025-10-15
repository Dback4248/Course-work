#include "raylib.h"
#include "animatronic.h"
void Animatronic::Init(const std::string& path)
{
    sprite = LoadTexture(path.c_str());
}

void Animatronic::Update()
{
    timer += GetFrameTime();
    if (timer > 10) active = true;
    if (active && GetRandomValue(0, 500) == 1)
        jumpscare = true;
}

bool Animatronic::CheckJumpscare()
{
    return jumpscare;
}

void Animatronic::Unload()
{
    UnloadTexture(sprite);
}

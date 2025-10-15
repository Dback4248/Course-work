#pragma once
#include "raylib.h"
#include <string>

class Animatronic
{
public:
    void Init(const std::string& path);
    void Update();
    void Unload();
    bool CheckJumpscare();

private:
    Texture2D sprite;
    float timer = 0;
    bool active = false;
    bool jumpscare = false;
};

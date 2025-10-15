#include "ui.h"
#include "raylib.h"

void UI::Init()
{
    jumpscareTex = LoadTexture("assets/jumpscare.png");
    jumpscareSound = LoadSound("assets/jumpscare.wav");
}

void UI::DrawMenu()
{
    DrawText("FIVE NIGHTS AT FREDDY'S", 300, 200, 50, WHITE);
    DrawText("Press ENTER to start", 480, 400, 20, GRAY);
}

void UI::DrawHUD(float power, float nightTime, bool dL, bool dR, bool lL, bool lR)
{
    DrawText(TextFormat("Power: %.1f%%", power), 20, 20, 20, GREEN);
    DrawText(TextFormat("Time: %.1f", nightTime), 20, 50, 20, WHITE);
    DrawText(TextFormat("Doors: L[%s] R[%s]", dL ? "Closed" : "Open", dR ? "Closed" : "Open"), 20, 80, 20, WHITE);
    DrawText(TextFormat("Lights: L[%s] R[%s]", lL ? "On" : "Off", lR ? "On" : "Off"), 20, 110, 20, YELLOW);
}

void UI::DrawJumpscare()
{
    DrawTexture(jumpscareTex, 0, 0, WHITE);
}

void UI::PlayJumpscare()
{
    if (!playing)
    {
        PlaySound(jumpscareSound);
        playing = true;
        jumpscareTimer = 0;
    }
    jumpscareTimer += GetFrameTime();
}

bool UI::IsJumpscareOver()
{
    return jumpscareTimer > 2.0f;
}

void UI::DrawGameOver()
{
    DrawText("GAME OVER", 500, 300, 50, RED);
    DrawText("Press ENTER to restart", 480, 400, 20, WHITE);
}

void UI::Unload()
{
    UnloadTexture(jumpscareTex);
    UnloadSound(jumpscareSound);
}

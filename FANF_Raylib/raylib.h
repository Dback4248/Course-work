#pragma once
#ifndef RAYLIB_STUB_H
#define RAYLIB_STUB_H

#ifdef USE_REAL_RAYLIB
// If using the actual Raylib, include the real header instead
#else

#include <cstdint>
#include <string>
#include <cmath>
#include <cstdarg>
#include <cstdio>

//--------------------------------------
// Core basic types
//--------------------------------------
typedef struct Color { unsigned char r, g, b, a; } Color;
typedef struct Vector2 { float x, y; } Vector2;
typedef struct Vector3 { float x, y, z; } Vector3;
typedef struct Vector4 { float x, y, z, w; } Vector4;
typedef struct Rectangle { float x, y, width, height; } Rectangle;
typedef struct Matrix {
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
} Matrix;

//--------------------------------------
// Cameras and transforms
//--------------------------------------
typedef struct Camera2D { Vector2 offset; Vector2 target; float rotation; float zoom; } Camera2D;
typedef struct Camera3D { Vector3 position; Vector3 target; Vector3 up; float fovy; int projection; } Camera3D;
typedef struct Transform { Vector3 translation; Vector4 rotation; Vector3 scale; } Transform;

//--------------------------------------
// Assets (textures, audio, models, etc.)
//--------------------------------------
typedef struct Texture2D { unsigned int id; int width; int height; int mipmaps; int format; } Texture2D;
typedef struct TextureCubemap { unsigned int id; int size; int format; } TextureCubemap;
typedef struct RenderTexture2D { unsigned int id; Texture2D texture; Texture2D depth; } RenderTexture2D;
typedef struct Mesh { int vertexCount; int triangleCount; float* vertices; } Mesh;
typedef struct Shader { unsigned int id; } Shader;
typedef struct Model { Mesh* meshes; int meshCount; Texture2D* materials; int materialCount; Matrix transform; } Model;
typedef struct ModelAnimation { int frameCount; int boneCount; } ModelAnimation;
typedef struct Material { Shader shader; } Material;
typedef struct Sound { unsigned int id; } Sound;
typedef struct Music { unsigned int id; } Music;

//--------------------------------------
// Color constants
//--------------------------------------
static const Color WHITE = { 255, 255, 255, 255 };
static const Color BLACK = { 0,   0,   0, 255 };
static const Color RED = { 230,  41,  55, 255 };
static const Color GREEN = { 0, 228,  48, 255 };
static const Color BLUE = { 0, 121, 241, 255 };
static const Color YELLOW = { 253, 249,   0, 255 };
static const Color ORANGE = { 255, 161,   0, 255 };
static const Color GRAY = { 130, 130, 130, 255 };
static const Color PURPLE = { 200, 122, 255, 255 };

//--------------------------------------
// Input key constants
//--------------------------------------
#define KEY_W            87
#define KEY_A            65
#define KEY_S            83
#define KEY_D            68
#define KEY_SPACE        32
#define KEY_ENTER        257
#define KEY_ESCAPE       256
#define KEY_LEFT         263
#define KEY_RIGHT        262
#define KEY_UP           265
#define KEY_DOWN         264
#define KEY_ONE          49
#define KEY_TWO          50
#define KEY_THREE        51
#define KEY_FOUR         52
#define MOUSE_LEFT_BUTTON   0
#define MOUSE_RIGHT_BUTTON  1

//--------------------------------------
// Window and drawing
//--------------------------------------
inline void InitWindow(int, int, const char*) {}
inline bool WindowShouldClose() { return false; }
inline void CloseWindow() {}
inline void BeginDrawing() {}
inline void EndDrawing() {}
inline void ClearBackground(Color) {}
inline void DrawText(const char*, int, int, int, Color) {}
inline void DrawRectangle(int, int, int, int, Color) {}
inline void DrawRectangleRec(Rectangle, Color) {}
inline void DrawCircle(int, int, float, Color) {}
inline void DrawLine(int, int, int, int, Color) {}
inline void DrawTriangle(Vector2, Vector2, Vector2, Color) {}
inline void DrawTexture(Texture2D, int, int, Color) {}
inline void DrawTextureEx(Texture2D, Vector2, float, float, Color) {}
inline void DrawTextureRec(Texture2D, Rectangle, Vector2, Color) {}
inline void DrawModel(Model, Vector3, float, Color) {}
inline void DrawModelEx(Model, Vector3, Vector3, float, Vector3, Color) {}
inline void DrawGrid(int, float) {}

//--------------------------------------
// Input functions
//--------------------------------------
inline bool IsKeyDown(int) { return false; }
inline bool IsKeyPressed(int) { return false; }
inline bool IsKeyReleased(int) { return false; }
inline bool IsMouseButtonDown(int) { return false; }
inline bool IsMouseButtonPressed(int) { return false; }
inline bool IsMouseButtonReleased(int) { return false; }
inline Vector2 GetMousePosition() { return { 0, 0 }; }

//--------------------------------------
// Audio functions
//--------------------------------------
inline void InitAudioDevice() {}
inline void CloseAudioDevice() {}
inline Sound LoadSound(const char*) { return {}; }
inline void PlaySound(Sound) {}
inline void StopSound(Sound) {}
inline void UnloadSound(Sound) {}
inline Music LoadMusicStream(const char*) { return {}; }
inline void PlayMusicStream(Music) {}
inline void UpdateMusicStream(Music) {}
inline void StopMusicStream(Music) {}
inline void UnloadMusicStream(Music) {}
inline void PauseMusicStream(Music) {}
inline void ResumeMusicStream(Music) {}

//--------------------------------------
// Texture management
//--------------------------------------
inline Texture2D LoadTexture(const char*) { return Texture2D{ 1, 64, 64, 1, 0 }; }
inline void UnloadTexture(Texture2D) {}

//--------------------------------------
// Shader & Model management
//--------------------------------------
inline Shader LoadShader(const char*, const char*) { return {}; }
inline void UnloadShader(Shader) {}
inline Model LoadModel(const char*) { return {}; }
inline void UnloadModel(Model) {}
inline void SetShaderValue(Shader, int, const void*, int) {}
inline void SetShaderValueMatrix(Shader, int, Matrix) {}

//--------------------------------------
// Physics & collision stubs
//--------------------------------------
inline bool CheckCollisionRecs(Rectangle r1, Rectangle r2) {
    return (r1.x < r2.x + r2.width && r1.x + r1.width > r2.x &&
        r1.y < r2.y + r2.height && r1.y + r1.height > r2.y);
}
inline bool CheckCollisionCircles(Vector2 c1, float r1, Vector2 c2, float r2) {
    float dx = c1.x - c2.x, dy = c1.y - c2.y;
    return (dx * dx + dy * dy) <= (r1 + r2) * (r1 + r2);
}
inline bool CheckCollisionBoxSphere(Vector3, Vector3, Vector3, float) { return false; }
inline bool CheckCollisionBoxes(Vector3, Vector3, Vector3, Vector3) { return false; }

//--------------------------------------
// Camera functions
//--------------------------------------
inline void BeginMode2D(Camera2D) {}
inline void EndMode2D() {}
inline void BeginMode3D(Camera3D) {}
inline void EndMode3D() {}
inline void UpdateCamera(Camera3D*) {}

//--------------------------------------
// Timing and system
//--------------------------------------
inline void SetTargetFPS(int) {}
inline int GetFPS() { return 60; }
inline double GetTime() { return 0.0; }
inline void DrawFPS(int, int) {}
inline float GetFrameTime() { return 0.016f; }

//--------------------------------------
// Misc utility
//--------------------------------------
inline int GetRandomValue(int min, int max) {
    return min + (std::rand() % ((max - min) + 1));
}

//--------------------------------------
// Text formatting
//--------------------------------------
inline const char* TextFormat(const char* fmt, ...) {
    static char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return buffer;
}

#endif // USE_REAL_RAYLIB
#endif // RAYLIB_STUB_H


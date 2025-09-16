#pragma once

namespace MathClasses
{
    struct Matrix4
    {
        float m[4][4];
        Matrix4() { for (int i = 0;i < 4;i++) for (int j = 0;j < 4;j++) m[i][j] = (i == j ? 1 : 0); }
    };
}

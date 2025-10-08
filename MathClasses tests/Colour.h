#pragma once
using Byte = unsigned char;

class Colour
{
private:
    unsigned int colour; // 32-bit RGBA

public:
    Colour() : colour(0) {}

    Colour(Byte red, Byte green, Byte blue, Byte alpha) {
        setRed(red);
        setGreen(green);
        setBlue(blue);
        setAlpha(alpha);
    }

    Byte getRed()   const { return (colour >> 24) & 0xFF; }
    Byte getGreen() const { return (colour >> 16) & 0xFF; }
    Byte getBlue()  const { return (colour >> 8) & 0xFF; }
    Byte getAlpha() const { return  colour & 0xFF; }

    void setRed(Byte red) {
        colour &= 0x00FFFFFF;
        colour |= (red << 24);
    }

    void setGreen(Byte green) {
        colour &= 0xFF00FFFF;
        colour |= (green << 16);
    }

    void setBlue(Byte blue) {
        colour &= 0xFFFF00FF;
        colour |= (blue << 8);
    }

    void setAlpha(Byte alpha) {
        colour &= 0xFFFFFF00;
        colour |= alpha;
    }

    unsigned int getValue() const { return colour; }
    void setValue(unsigned int value) { colour = value; }
};


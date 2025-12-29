#pragma once

#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

struct Point
{
    int16_t x;
    int16_t y;
};

class ScreenArea
{
public:
    ScreenArea(int16_t x, int16_t y, int16_t width, int16_t height) : m_x(x), m_y(y), m_width(width), m_height(height) {}

protected:
    const int16_t m_x;
    const int16_t m_y;
    const int16_t m_width;
    const int16_t m_height;
    bool m_mustDraw = true;

protected:
    void clear(uint16_t color);

protected:
    virtual void redraw() = 0;
    virtual void touch(const Point &pt);

public:
    virtual bool touchTest(const Point &pt);
    virtual void redrawTest();

public:
    static bool touchToScreen(Point &pt);

protected:
    static Adafruit_ILI9341 s_display;
    static XPT2046_Touchscreen s_touch;

public:
    static void setup();
};

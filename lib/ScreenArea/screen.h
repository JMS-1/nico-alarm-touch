#pragma once

#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define TOUCH_X_MIN 390
#define TOUCH_X_MAX 3900
#define TOUCH_Y_MIN 290
#define TOUCH_Y_MAX 3800
#define TOUCH_WIDTH (TOUCH_X_MAX - TOUCH_X_MIN)
#define TOUCH_HEIGHT (TOUCH_Y_MAX - TOUCH_Y_MIN)

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
    static Adafruit_ILI9341 s_display;
    static XPT2046_Touchscreen s_touch;

public:
    void clear(uint16_t color = ILI9341_BLACK);

protected:
    virtual void redraw() = 0;
    virtual void touch(const Point &pt);

public:
    virtual void touchTest(const Point &pt);
    virtual void redrawTest();
    virtual void loop();
    virtual void setup();

public:
    static bool touchToScreen(Point &pt);

public:
    static void hide();
    static void show();
};

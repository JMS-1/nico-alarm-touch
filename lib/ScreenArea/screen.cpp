#include "screen.h"

Adafruit_ILI9341 ScreenArea::s_display(5, 4, 22);
XPT2046_Touchscreen ScreenArea::s_touch(14, 27);

static bool hidden = false;
static bool mustSetup = true;

void ScreenArea::clear(uint16_t color)
{
    s_display.fillRect(m_x, m_y, m_width, m_height, color);
}

void ScreenArea::touch(const Point &pt) {}

void ScreenArea::loop() {}

void ScreenArea::touchTest(const Point &pt)
{
    if (hidden)
        return;

    if (pt.x < m_x || pt.x >= m_x + m_width)
        return;
    if (pt.y < m_y || pt.y >= m_y + m_height)
        return;

    touch(pt);
}

void ScreenArea::redrawTest()
{
    if (!m_mustDraw && !hidden)
        return;

    m_mustDraw = false;

    redraw();
}

bool ScreenArea::touchToScreen(Point &pt)
{
    pt.x = 0;
    pt.y = 0;

    if (!s_touch.touched())
        return false;

    auto point = s_touch.getPoint();

    pt.x = max(0, min(TFT_WIDTH, (point.x - TOUCH_X_MIN) * TFT_WIDTH / TOUCH_WIDTH));
    pt.y = max(0, min(TFT_HEIGHT, (point.y - TOUCH_Y_MIN) * TFT_HEIGHT / TOUCH_HEIGHT));

    return true;
}

void ScreenArea::setup()
{
    if (!mustSetup)
        return;

    mustSetup = false;

    pinMode(15, OUTPUT);
    digitalWrite(15, LOW);

    s_display.begin();
    s_display.setRotation(3);

    s_touch.begin();
    s_touch.setRotation(1);

    s_display.fillScreen(ILI9341_BLACK);
}

void ScreenArea::hide()
{
    if (hidden)
        return;

    hidden = true;

    s_display.fillScreen(ILI9341_BLACK);
}

void ScreenArea::show()
{
    hidden = false;
}
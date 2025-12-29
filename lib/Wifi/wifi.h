#pragma once

#include <screen.h>

class WifiButton : public ScreenArea
{
public:
    WifiButton() : ScreenArea(100, 100, 50, 50) {}

private:
    uint16_t m_color = ILI9341_MAGENTA;

protected:
    void redraw();
    void touch(const Point &pt);
};

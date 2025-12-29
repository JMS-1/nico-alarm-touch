#include "wifi.h"

void WifiButton::redraw()
{
    clear(m_color);
}

void WifiButton::touch(const Point &pt)
{
    m_color = m_color == ILI9341_MAGENTA ? ILI9341_DARKCYAN : ILI9341_MAGENTA;
    m_mustDraw = true;
}

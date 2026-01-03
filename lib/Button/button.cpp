#include "button.h"

void Button::redraw()
{
    clear();

    if (!m_visible)
        return;

    s_display.fillRoundRect(m_x, m_y, m_width, m_height, 10, ILI9341_GREEN);
    s_display.setCursor(m_x + 8, m_y + 8);
    s_display.setTextColor(ILI9341_BLACK);
    s_display.setTextSize(2);
    s_display.setTextWrap(false);
    s_display.println(m_text);
}

void Button::setVisible(bool visible)
{
    if (visible == m_visible)
        return;

    m_visible = visible;
    m_mustDraw = true;
}

void Button::onClick(THandler handler)
{
    m_click = handler;
}

void Button::touch(const Point &pt)
{
    if (m_click != nullptr)
        m_click();
}
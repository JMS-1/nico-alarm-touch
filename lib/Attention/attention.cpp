#include "attention.h"

void Attention::redraw()
{
    clear();

    if (!m_started)
        return;

    auto centerX = m_x + m_width / 2;
    auto centerY = m_y + m_height / 2;

    for (auto delta = 2; delta < 30; delta++)
    {
        auto color =
            delta < 10
                ? ILI9341_RED
            : delta < 21
                ? ILI9341_YELLOW
                : ILI9341_GREENYELLOW;

        auto startWidth = (m_width - delta) / 2;
        auto endWidth = max(1, startWidth - 5);

        while (startWidth >= endWidth)
            s_display.drawCircle(centerX, centerY, startWidth--, color);
    }

    delay(100);
}

void Attention::start()
{
    m_started = millis();
    m_mustDraw = true;
}

void Attention::stop()
{
    m_started = 0;
    m_mustDraw = true;
}

void Attention::loop()
{
    ScreenArea::loop();

    if (!m_started)
        return;

    if (millis() - m_started > 15000)
        stop();
    else
        m_mustDraw = true;
}
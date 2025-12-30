#pragma once

#include <screen.h>

class Text : public ScreenArea
{
public:
    Text(int y) : ScreenArea(0, y, TFT_WIDTH, TFT_HEIGHT - y) {}

private:
    String m_text;

public:
    void setText(const String &text);

protected:
    void redraw();
};
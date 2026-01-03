#pragma once

#include <screen.h>

class Button : public ScreenArea
{
public:
    Button(const String &text, int x, int y, int width, int height, bool initialVisible = true) : ScreenArea(x, y, width, height), m_text(text), m_visible(initialVisible), m_click(nullptr) {}

public:
    typedef std::function<void()> THandler;

private:
    bool m_visible;
    const String m_text;
    THandler m_click;

public:
    void onClick(THandler handler);
    void setVisible(bool visible);

protected:
    void redraw();
    void touch(const Point &pt);
};
#pragma once

#include <screen.h>

class Attention : public ScreenArea
{
public:
    Attention() : ScreenArea(5, 5, 50, 50), m_started(0) {}

protected:
    void redraw();

private:
    unsigned long m_started;

public:
    void start();
    void stop();
    void loop();
};
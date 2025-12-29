#pragma once

#include <screen.h>

class WifiButton : public ScreenArea
{
public:
    WifiButton() : ScreenArea(TFT_WIDTH - 60, 5, 40, 40) {}

private:
    enum state_t
    {
        CONNECTING,
        WPS,
        CONNECTED
    };

    state_t m_state = CONNECTING;

protected:
    void redraw();
    void touch(const Point &pt);

public:
    void loop();
};

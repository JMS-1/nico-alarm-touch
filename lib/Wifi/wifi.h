#pragma once

#include <screen.h>

class WifiButton : public ScreenArea
{
public:
    WifiButton() : ScreenArea(TFT_WIDTH - 60, 5, 40, 40) {}

protected:
    void redraw();
    void touch(const Point &pt);

public:
    bool isConnected();
    void loop();
    void setup();
};

#include <screen.h>
#include <wifi.h>

int16_t lastX = -1;
int16_t lastY = -1;

ScreenArea *areas[] = {new WifiButton()};

void setup()
{
    Serial.begin(115200);

    ScreenArea::setup();
}

void loop(void)
{
    auto debounce = false;

    Point pt;
    if (ScreenArea::touchToScreen(pt))
        if (pt.x != lastX && pt.y != lastY)
            for (auto area : areas)
                if (area->touchTest(pt))
                    debounce = true;

    for (auto area : areas)
        area->redrawTest();

    if (debounce)
        delay(500);
}
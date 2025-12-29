#include <screen.h>
#include <wifi.h>

int16_t lastX = -1000;
int16_t lastY = -1000;

time_t lastTouch = time(nullptr);

ScreenArea *areas[] = {new WifiButton()};

void setup()
{
    Serial.begin(115200);

    for (auto area : areas)
        area->setup();
}

void loop(void)
{
    // Check for a touch.
    Point pt;
    if (ScreenArea::touchToScreen(pt))
    {
        // Remember time of last user interaction.
        lastTouch = time(nullptr);

        // Forward to all areas if.
        if (abs(pt.x - lastX) >= 5 || abs(pt.y - lastY) >= 5)
            for (auto area : areas)
                area->touchTest(pt);

        // Remember last touch.
        lastX = pt.x;
        lastY = pt.y;
    }
    else
    {
        lastX = -1000;
        lastY = -1000;
    }

    // Test for redraw.
    if (difftime(time(nullptr), lastTouch) >= 15)
        ScreenArea::hide();
    else
    {
        for (auto area : areas)
            area->redrawTest();

        ScreenArea::show();

        delay(500);
    }

    // Do background processing.
    for (auto area : areas)
        area->loop();
}
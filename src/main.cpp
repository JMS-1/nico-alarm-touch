#include <api.h>
#include <screen.h>
#include <text.h>
#include <wifi.h>

int16_t lastX = -1000;
int16_t lastY = -1000;

time_t lastTouch = time(nullptr);

ApiServer api;

Text message(80);
Text when(50);
WifiButton wifi;

ScreenArea *areas[] = {&wifi, &when, &message};

void setup()
{
    Serial.begin(115200);

    for (auto area : areas)
        area->setup();
}

void loop(void)
{
    // Time to setup web server.
    api.loop(
        wifi.isConnected(),
        [](const String &newWhen, const String &newMessage)
        {
            when.setText(newWhen);
            message.setText(newMessage);

            lastTouch = time(nullptr);
        });

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
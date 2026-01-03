#include <api.h>
#include <attention.h>
#include <button.h>
#include <screen.h>
#include <text.h>
#include <wifi.h>
#include "Arduino.h"

int16_t lastX = -1000;
int16_t lastY = -1000;

time_t lastTouch = time(nullptr);

ApiServer api;

Attention attention;
Button off("Gesehen", 10, 180, 100, 30, false);
Text message(100);
Text when(70);
WifiButton wifi;

ScreenArea *areas[] = {&when, &message, &off, &wifi, &attention};

void apiCommand(const String &newWhen, const String &newMessage)
{
    when.setText(newWhen);
    message.setText(newMessage);
    off.setVisible(!newWhen.isEmpty());

    lastTouch = time(nullptr);

    if (newMessage.isEmpty())
        attention.stop();
    else
        attention.start();
}

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Startup...");

    off.onClick(
        []
        { api.off(apiCommand); });

    for (auto area : areas)
        area->setup();

    Serial.println("Ready");
}

void loop(void)
{
    // Time to setup web server.
    api.loop(wifi.isConnected(), apiCommand);

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
    if (difftime(time(nullptr), lastTouch) >= 30)
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

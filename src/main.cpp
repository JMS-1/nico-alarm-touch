#include "SPI.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <SD.h>
#include <image.h>

Adafruit_ILI9341 tft = Adafruit_ILI9341(5, 4, 22);
XPT2046_Touchscreen ts(14, 27);

#define TOUCH_X_MIN 390
#define TOUCH_X_MAX 3900
#define TOUCH_Y_MIN 290
#define TOUCH_Y_MAX 3800
#define TOUCH_WIDTH (TOUCH_X_MAX - TOUCH_X_MIN)
#define TOUCH_HEIGHT (TOUCH_Y_MAX - TOUCH_Y_MIN)

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

int lastX = -1;
int lastY = -1;

struct Point
{
    int x;
    int y;
};

Point touchToScreen(const TS_Point &point)
{
    Point pt = {0, 0};

    pt.x = max(0, min(TFT_WIDTH, (point.x - TOUCH_X_MIN) * TFT_WIDTH / TOUCH_WIDTH));
    pt.y = max(0, min(TFT_HEIGHT, (point.y - TOUCH_Y_MIN) * TFT_HEIGHT / TOUCH_HEIGHT));

    return pt;
}

void setup()
{
    pinMode(15, OUTPUT);
    digitalWrite(15, LOW);

    Serial.begin(115200);

    tft.begin();
    tft.setRotation(3);

    ts.begin();
    ts.setRotation(1);

    tft.fillScreen(ILI9341_LIGHTGREY);
}

void loop(void)
{
    if (ts.touched())
    {
        auto pt = touchToScreen(ts.getPoint());

        if (pt.x != lastX && pt.y != lastY)
        {
            tft.fillScreen(ILI9341_BLACK);
            tft.drawRGBBitmap(lastX = pt.x, lastY = pt.y, Image::getData(), 100, 75);
        }
    }

    delay(100);
}
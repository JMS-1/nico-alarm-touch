#include "text.h"

String utf8ToGFX(const String &utf8)
{
    String codePage437;

    for (auto i = 0; i < utf8.length(); i++)
    {
        auto c = utf8[i];

        if ((c & 0xE0) != 0xC0)
            codePage437 += c;
        else
        {
            if (++i >= utf8.length())
                break;

            char c2 = utf8[i];

            switch (c2)
            {
            case 0xA4:
                codePage437 += (char)0x84; // ä
                break;
            case 0xB6:
                codePage437 += (char)0x94; // ö
                break;
            case 0xBC:
                codePage437 += (char)0x81; // ü
                break;
            case 0x9F:
                codePage437 += (char)0xE1; // ß
                break;
            case 0x84:
                codePage437 += (char)0x8E; // Ä
                break;
            case 0x96:
                codePage437 += (char)0x99; // Ö
                break;
            case 0x9C:
                codePage437 += (char)0x9A; // Ü
                break;
            default:
                codePage437 += "?";
                break;
            }
        }
    }

    return codePage437;
}

void Text::redraw()
{
    s_display.cp437(true);
    s_display.setCursor(m_x, m_y);
    s_display.setTextColor(ILI9341_WHITE);
    s_display.setTextSize(2);
    s_display.setTextWrap(true);
    s_display.println(m_text);
}

void Text::setText(const String &text)
{
    m_text = utf8ToGFX(text);
    m_mustDraw = true;
}

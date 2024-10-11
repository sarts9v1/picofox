#include <ctype.h>
#include <string>
#include "pico/stdlib.h"

#include "main.h"

std::string morseCode[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",                   // A-J
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",                     // K-T
    "..-", "...-", ".--", "-..-", "-.--", "--..",                                            // U-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." // 0-9
};

// Function to convert a character to its Morse code equivalent
std::string charToMorse(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return morseCode[c - 'A'];
    }
    if (c >= 'a' && c <= 'z')
    {
        return morseCode[c - 'a'];
    }
    if (c >= '0' && c <= '9')
    {
        return morseCode[c - '0' + 26];
    }
    if (c == '0')
    {
        return " ";
    }
    return std::string{}; // Return empty string for unsupported characters
}

void playMorse(const char *str, int wpm)
{
    while (*str)
    {
        char c = *str;
        if (c == ' ')
        {
            sleep_ms(7 * 400 / wpm);
        }
        else
        {
            for (auto m : charToMorse(c))
            {
                if (m == '.')
                {
                    out_enable();
                    sleep_ms(1200 / wpm);
                    out_disable();
                }
                else if (m == '-')
                {
                    out_enable();
                    sleep_ms(3600 / wpm);
                    out_disable();
                }
                sleep_ms(1200 / wpm);
            }
            sleep_ms(2400 / wpm);
        }
        str++;
    }
}

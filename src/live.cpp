#include <Arduino.h>

#define DATA 5
#define SHIFT 7
#define STORE 6

void store();
int happy[] = {0, 16, 38, 32, 32, 38, 16, 0};
int SKULL[] = {56, 110, 207, 191, 239, 207, 63, 62};
int heart[] = {28, 62, 126, 252, 252, 126, 62, 28};

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello, world!");

    pinMode(DATA, OUTPUT);
    pinMode(SHIFT, OUTPUT);
    pinMode(STORE, OUTPUT);

}

void loop()
{
    // Check if there is any serial data available.
    if (Serial.available()) {
        // Read the incoming string until the closing brace '}'.
        String s = Serial.readStringUntil('}');
        int openBraceIndex = s.indexOf('{');
        if (openBraceIndex >= 0) {
            // Get the substring inside the braces.
            s = s.substring(openBraceIndex + 1);
            int index = 0;
            // Expect exactly 8 numbers.
            for (int i = 0; i < 8; i++) {
                int commaIndex = s.indexOf(',', index);
                String numStr;
                if (commaIndex != -1) {
                    numStr = s.substring(index, commaIndex);
                    index = commaIndex + 1;
                } else {
                    numStr = s.substring(index);
                }
                numStr.trim();
                happy[i] = numStr.toInt();
                Serial.print(happy[i]);
                Serial.print(" ");
            }
            Serial.println();
        }
    }

    // Use the parsed numbers to control the LED matrix.
    for (int i = 0; i < 8; i++)
    {
            shiftOut(DATA, SHIFT, MSBFIRST, ~happy[i]);
            shiftOut(DATA, SHIFT, MSBFIRST, 128 >> i);
            store();
    }
}

void store()
{
  digitalWrite(STORE, HIGH);
  delayMicroseconds(10);
  digitalWrite(STORE, LOW);
  delayMicroseconds(10);
}
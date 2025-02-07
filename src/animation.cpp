// #include <Arduino.h>

// #define DATA 5
// #define SHIFT 7
// #define STORE 6

// void show(int *pattern, int duration);

// int animation[6][8] = {
//     {255, 129, 129, 129, 129, 129, 129, 255},
//     {0, 126, 66, 66, 66, 66, 126, 0},
//     {0, 0, 60, 36, 36, 60, 0, 0},
//     {0, 0, 0, 24, 24, 0, 0, 0},
//     {0, 0, 60, 36, 36, 60, 0, 0},
//     {0, 126, 66, 66, 66, 66, 126, 0}};

// void setup()
// {
//     pinMode(DATA, OUTPUT);
//     pinMode(SHIFT, OUTPUT);
//     pinMode(STORE, OUTPUT);
// }

// void loop()
// {
//     for (int i= 0; i < 6; i++) {
//         show(animation[i], 100);
//     }
// }

// void show(int *pattern, int duration) {
//     unsigned long start = millis();
//     while (millis() - start < duration)
//     {
//         for (int i = 0; i < 8; i++)
//         {
//             shiftOut(DATA, SHIFT, MSBFIRST, ~pattern[i]);
//             shiftOut(DATA, SHIFT, MSBFIRST, 128 >> i);
//             digitalWrite(STORE, HIGH);
//             delayMicroseconds(10);
//             digitalWrite(STORE, LOW);
//             delayMicroseconds(10);
//         }
//     }

// }
// #include <Arduino.h>

// #define DATA 5
// #define SHIFT 7
// #define STORE 6

// int speed = 500;

// unsigned long start_time;
// void show(int *pattern, int duration);

// int heart[] = {28, 62, 126, 252, 252, 126, 62, 28};
// int j[] = {0, 0, 3, 2, 2, 0, 0, 0};


// void setup()
// {
//   pinMode(DATA, OUTPUT);
//   pinMode(SHIFT, OUTPUT);
//   pinMode(STORE, OUTPUT);

//   start_time = millis();
// }

// void loop()
// {
//   if (millis() % speed == 0)
//   {

//     show(j, speed-50);

//     for (int i = 0; i < 8; i++)
//     {
//       j[i] = j[i] << 1;
//     }
//   }
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

// //https: // chat.qwenlm.ai/c/8efd88bd-5502-437b-87bc-c4b9358b17b3
// //teris qwen 2.5 max
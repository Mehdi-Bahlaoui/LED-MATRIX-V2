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
  pinMode(DATA, OUTPUT);
  pinMode(SHIFT, OUTPUT);
  pinMode(STORE, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 8; i++)
  {
    shiftOut(DATA, SHIFT, MSBFIRST, ~heart[i]);
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
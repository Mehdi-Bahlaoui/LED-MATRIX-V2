#include <Arduino.h>

#define DATA 5
#define SHIFT 7
#define STORE 6

unsigned long speed = 500;
unsigned long lastUpdateTime = 0;

void show(uint8_t *pattern);

struct Snake
{
    uint8_t length = 3;
    uint8_t pos[8] = {1, 1, 1, 0, 0, 0, 0, 0};
    // uint8_t dir = 0; // 0: up, 1: right, 2: down, 3: left
    //head_pos
};

struct Apple
{
    const uint8_t length = 1;
    uint8_t pos[8] = {0, 0, 0, 0, 16, 0, 0, 0};
};

// Create instances of the structs
Snake snake;
Apple apple;

void setup(){
    Serial.begin(9600);
    Serial.println("Tetris Game:");

    pinMode(DATA, OUTPUT);
    pinMode(SHIFT, OUTPUT);
    pinMode(STORE, OUTPUT);

}


void loop(){

unsigned long currentTime = millis();

// Game update
if (currentTime - lastUpdateTime >= speed)
{
    // updateGame();
    lastUpdateTime = currentTime;
}

// Rendering
show(snake.pos);
show(apple.pos);
}


// function for displaying any pattern
void show(uint8_t *pattern)
{
    for (int i = 0; i < 8; i++)
    {
        shiftOut(DATA, SHIFT, MSBFIRST, ~pattern[i]);
        shiftOut(DATA, SHIFT, MSBFIRST, 0x80 >> i);
        digitalWrite(STORE, HIGH);
        delayMicroseconds(10);
        digitalWrite(STORE, LOW);
    }
}
#include <Arduino.h>
#include <math.h>

#define DATA 5
#define STORE 6
#define SHIFT 7

unsigned long speed = 500;
unsigned long lastUpdateTime = 0;
char direction = 'd';
bool gameOver = false;

void show(uint8_t *pattern);
void updateGame();
void spawnApple();
bool checkCollision(uint8_t x, uint8_t y);

struct Point {
    uint8_t x;
    uint8_t y;
};

struct Snake {
    Point segments[64]; // Max snake length (8x8 grid)
    uint8_t length = 3;
    char dir = 'd';
    
    // Initialize snake in the top-left corner
    Snake() {
        segments[0] = {0, 0};
        segments[1] = {0, 1};
        segments[2] = {0, 2};
    }
};

struct Apple {
    Point pos;
    
    Apple() {
        pos = {static_cast<uint8_t>(random(8)), static_cast<uint8_t>(random(8))};
    }
};

Snake snake;
Apple apple;

void setup() {
    Serial.begin(9600);
    Serial.println("Snake Game:");

    pinMode(DATA, OUTPUT);
    pinMode(SHIFT, OUTPUT);
    pinMode(STORE, OUTPUT);
    
}

void loop() {
    if (gameOver) {
        // Display game over pattern or restart
        return;
    }

    unsigned long currentTime = millis();
    // Game update
    if (currentTime - lastUpdateTime >= speed) {
        updateGame();
        lastUpdateTime = currentTime;
    }

    // Render game
    uint8_t display[8] = {0};
    
    // Draw apple
    display[apple.pos.y] |= (1 << apple.pos.x);
    
    // Draw snake
    for (uint8_t i = 0; i < snake.length; i++) {
        display[snake.segments[i].y] |= (1 << snake.segments[i].x);
    }
    
    show(display);

    // Handle input
    if (Serial.available()) {
        char input = Serial.read();
        // Prevent 180-degree turns
        if ((input == 'd' && snake.dir != 'a') || 
            (input == 'a' && snake.dir != 'd') ||
            (input == 'w' && snake.dir != 's') || 
            (input == 's' && snake.dir != 'w')) {
            direction = input;

            Serial.println(String("Direction: ") + direction);
        }
    }
}

void show(uint8_t *pattern) {
    for (int i = 0; i < 8; i++) {
        shiftOut(DATA, SHIFT, MSBFIRST, ~pattern[i]);
        shiftOut(DATA, SHIFT, MSBFIRST, 0x80 >> i);
        digitalWrite(STORE, HIGH);
        delayMicroseconds(10);
        digitalWrite(STORE, LOW);
    }
}

void updateGame() {
    // Update snake direction
    snake.dir = direction;
    
    // Calculate new head position
    Point newHead = snake.segments[snake.length - 1];
    
    switch (snake.dir) {
        case 's': newHead.x++; break;
        case 'w': newHead.x--; break;
        case 'a': newHead.y--; break;
        case 'd': newHead.y++; break;
    }
    
    // Check wall collisions to wrap around
    if (newHead.x == 8) newHead.x = 0;
    else if (newHead.x == 255) newHead.x = 7; // Handle underflow for uint8_t
    if (newHead.y == 8) newHead.y = 0;
    else if (newHead.y == 255) newHead.y = 7; // Handle underflow for uint8_t
    else if (newHead.y < 0) newHead.y = 7;
    
    // Check self collision
    for (uint8_t i = 0; i < snake.length - 1; i++) {
        if (newHead.x == snake.segments[i].x && newHead.y == snake.segments[i].y) {
            gameOver = true;
            return;
        }
    }
    
    // Check if apple eaten
    bool ateApple = (newHead.x == apple.pos.x && newHead.y == apple.pos.y);
    
    // Move snake
    if (!ateApple) {
        // Shift all segments back
        for (uint8_t i = 0; i < snake.length - 1; i++) {
            snake.segments[i] = snake.segments[i + 1];
        }
    } else {
        // Increase length (new segment added at end)
        if (snake.length < 64) snake.length++;
        spawnApple();
    }
    
    // Add new head
    snake.segments[snake.length - 1] = newHead;
}

void spawnApple() {
    do {
        apple.pos.x = random(8);
        apple.pos.y = random(8);
        
        // Check if apple spawns on snake
        bool onSnake = false;
        for (uint8_t i = 0; i < snake.length; i++) {
            if (apple.pos.x == snake.segments[i].x && 
                apple.pos.y == snake.segments[i].y) {
                onSnake = true;
                break;
            }
        }
        
        if (!onSnake) break;
    } while (true);
}
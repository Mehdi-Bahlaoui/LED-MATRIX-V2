#include <Arduino.h>

#define DATA 5
#define SHIFT 7
#define STORE 6

#define RIGHT 8
#define LEFT 9

int speed = 500;
unsigned long lastUpdateTime = 0;
unsigned long lastInputTime = 0;
const int debounceDelay = 200;

void updateGame();
bool reachedBottom();
bool collided();
void getRandom();
bool gameOver();
void clear();
void show(int *pattern);
void moveBlock(char move);
int checkFullRows();
void removeLine(int row);
bool canMove(char direction);

int heart[] = {28, 62, 126, 252, 252, 126, 62, 28};

char currentMove;
bool moved = false;

int grid[] = {0, 0, 0, 0, 0, 0, 0, 0};
int block[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blocks[8][8] = {
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 3, 3, 0, 0, 0},
    {0, 0, 0, 3, 2, 2, 0, 0},
    {0, 0, 2, 2, 3, 0, 0, 0},
    {0, 0, 1, 3, 2, 0, 0, 0},
    {0, 0, 0, 2, 3, 1, 0, 0},
    {0, 0, 2, 3, 2, 0, 0, 0}};

void setup()
{
    Serial.begin(9600);
    Serial.println("Tetris Game:");

    pinMode(DATA, OUTPUT);
    pinMode(SHIFT, OUTPUT);
    pinMode(STORE, OUTPUT);

    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(LEFT, INPUT_PULLUP);

    getRandom();
}

void loop()
{
    unsigned long currentTime = millis();

    // Game update
    if (currentTime - lastUpdateTime >= speed)
    {
        updateGame();
        lastUpdateTime = currentTime;
    }

    // Input handling with debouncing
    if (millis() - lastInputTime > debounceDelay)
    {
        if (digitalRead(RIGHT) == LOW)
        {
            currentMove = 'r';
            moved = false;
            lastInputTime = millis();
        }
        else if (digitalRead(LEFT) == LOW)
        {
            currentMove = 'l';
            moved = false;
            lastInputTime = millis();
        }
    }

    // Rendering
    show(grid);
    show(block);
}

void moveBlock(char move)
{
    if (move == 'r')
    {
        for (int i = 7; i > 0; i--)
        {
            block[i] = block[i - 1];
        }
        block[0] = 0;
    }
    else if (move == 'l')
    {
        for (int i = 0; i < 7; i++)
        {
            block[i] = block[i + 1];
        }
        block[7] = 0;
    }
}

int checkFullRows()
{
    // Check from bottom to top (row 0 is bottom)
    for (int row = 0; row < 8; row++)
    {
        bool full = true;
        for (int col = 0; col < 8; col++)
        {
            if (!(grid[col] & (1 << row)))
            {
                full = false;
                break;
            }
        }
        if (full)
            return row;
    }
    return -1;
}

void removeLine(int row)
{
    Serial.println("Row removed");
    // For each column, shift all bits above the removed row down by one
    for (int col = 0; col < 8; col++)
    {
        int lower = grid[col] & ((1 << row) - 1);  // bits below the removed row remain unchanged
        int upper = grid[col] & ~((1 << (row + 1)) - 1);  // bits from the removed row upward
        grid[col] = lower<<1 | (upper);
    }
}

void updateGame()
{

    // Check and remove full rows
    int fullRow;
    while ((fullRow = checkFullRows()) != -1)
    {
        clear(); //easy mode
        // removeLine(fullRow); ////hard mode
    }

    // Game over check
    if (gameOver())
    {
        clear();
        return;
    }

    // Block landing logic
    if (reachedBottom() || collided())
    {
        // Merge with grid
        for (int i = 0; i < 8; i++)
        {
            grid[i] |= block[i];
        }
        getRandom();
    }
    else
    {
        // Move down
        for (int i = 0; i < 8; i++)
        {
            block[i] <<= 1;
        }
    }

    // Handle movement
    if (!moved && (currentMove == 'l' || currentMove == 'r'))
    {
        moveBlock(currentMove);
        moved = true;
    }
}

bool reachedBottom()
{
    for (int i = 0; i < 8; i++)
    {
        if (block[i] & 0x80)
            return true;
    }
    return false;
}

bool collided()
{
    for (int i = 0; i < 8; i++)
    {
        if ((block[i] << 1) & grid[i])
            return true;
    }
    return false;
}

void getRandom()
{
    int randomBlock = random(0, 8);
    for (int i = 0; i < 8; i++)
    {
        block[i] = blocks[randomBlock][i];
    }
}

bool gameOver()
{
    for (int i = 0; i < 8; i++)
    {
        if (grid[i] & 0x01)
            return true;
    }
    return false;
}

void clear()
{
    for (int i = 0; i < 8; i++)
    {
        grid[i] = 0;
    }
}

//function for displaying any pattern
void show(int *pattern)
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
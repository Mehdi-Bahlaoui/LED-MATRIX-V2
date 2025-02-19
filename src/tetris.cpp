#include <Arduino.h>

#define DATA 5
#define SHIFT 7
#define STORE 6

int speed = 500;
unsigned long lastUpdateTime = 0;

void updateGame();
bool reachedBottom();
bool collided();
void getRandom();
bool gameOver();
void clear();
void show(int *pattern);

int heart[] = {28, 62, 126, 252, 252, 126, 62, 28};

int grid[] = {0, 0, 0, 0, 0, 0, 0, 0};
int block[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blocks[8][8] = {{0, 0, 1, 1, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 0, 0, 0},
                    {0, 0, 0, 3, 3, 0, 0, 0},
                    {0, 0, 0, 3, 2, 2, 0, 0},
                    {0, 0, 2, 2, 3, 0, 0, 0},
                    {0, 0, 1, 3, 2, 0, 0, 0},
                    {0, 0, 0, 2, 3, 1, 0, 0},
                    {0, 0, 2, 3, 2, 0, 0, 0}};

void setup(){

    pinMode(DATA, OUTPUT);
    pinMode(SHIFT, OUTPUT);
    pinMode(STORE, OUTPUT);

    //getting first random block
    getRandom();

}

void loop(){

    unsigned long currentTime = millis();

    // Update game logic at regular intervals
    if (currentTime - lastUpdateTime >= speed)
    {
        updateGame();
        lastUpdateTime = currentTime;
    }

    // Render the display as fast as possible
    show(grid);
    show(block);
}

bool reachedBottom(){
    for (int i = 0; i < 8; i++)
    {
        if (block[i] & 128)
        {
            return true;
        }
    }
    return false;
}

bool collided(){
    for (int i = 0; i < 8; i++)
    {
        if ((block[i]<<1) & grid[i])
        {
            return true;
        }
    }
    return false;
}

void getRandom(){
    int randomBlock = random(0, 8);
    for (int i = 0; i < 8; i++)
    {
        block[i] = blocks[randomBlock][i];
    }
}

bool gameOver(){
    for (int i = 0; i < 8; i++){
        if (grid[i] & 1)
        {
            return true;        
        }
    }
    return false;
}

void clear(){
    for (int i = 0; i < 8; i++){
        grid[i] = 0;
    }
}

void updateGame(){   

    //check if game is over
    if (gameOver()) {
        clear();
        return;
    }
    
    // check if block reaches bottom or collides with existing bocks
    if (reachedBottom() || collided())
    {
        // Merge peice to grid
        for (int i = 0; i < 8; i++)
        {
            grid[i] = grid[i] | block[i];
        }

        // Check for full rows after move is implemented
        // for (int i = 0; i < 8; i++)
        // {
        //     if (grid[i] == 255)
        //     {
        //         // Remove the row
        //         for (int j = i; j > 0; j--)
        //         {
        //             grid[j] = grid[j - 1];
        //         }
        //         grid[0] = 0;
        //     }
        // }

        // get random block from blocks
        getRandom();


    }
    else
    {
        // Move the piece down
        for (int i = 0; i < 8; i++)
        {
            block[i] = block[i] << 1;
        }
    }
}

void show(int *pattern) {

    for (int i = 0; i < 8; i++)
    {
        shiftOut(DATA, SHIFT, MSBFIRST, ~pattern[i]);
        shiftOut(DATA, SHIFT, MSBFIRST, 128 >> i);
        digitalWrite(STORE, HIGH);
        delayMicroseconds(10);
        digitalWrite(STORE, LOW);
        delayMicroseconds(10);
    }
    

}


//https: // chat.qwenlm.ai/c/8efd88bd-5502-437b-87bc-c4b9358b17b3
//teris qwen 2.5 max
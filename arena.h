//
//  arena.h
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//
#ifndef arena_h
#define arena_h
#include "globals.h"
#include <vector>

class Snake;
class Fruit;
class Arena
{
public:
    Arena();
    void update();      //update snake position, fruit position
    void draw();        //draw the arena, snake, and fruit
    
    //Accessors
    Snake* head() const;
    bool gameOver() const;
    bool gameWon() const;
    char nextChar() const;
    
    //Mutators
    void spawnFruit();
    void moveSnake();
    void updateSnake();
    void growSnake();
    void setGameOver();
    void setGameWon();
    void redrawBounds();
    
    ~Arena();
    
private:
    char mGrid[ROWS][COLS];
    int lenSnake;
    int mScore;
    bool mGameOver;
    bool mGameWon;
    Snake* mHead;
    Fruit* mFruit;
    
    std::vector<Snake*> snake;
};

#endif /* arena_h */


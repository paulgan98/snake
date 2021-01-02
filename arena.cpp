//
//  arena.cpp
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#include "arena.h"
#include "snake.h"
#include "fruit.h"
#include "utilities.h"
#include <iostream>
using namespace std;

Arena::Arena() :
lenSnake(0),
mScore(0),
mFruit(nullptr),
mHead(nullptr),
mGameOver(false)
{
    //set top and bottom bounds in mGrid
    for (int c=0; c<COLS; c++)
    {
        mGrid[0][c] = '#';
        mGrid[ROWS-1][c] = '#';
    }
    
    //set left and right bounds in mGrid
    for (int r=1; r<ROWS-1; r++)
    {
        for (int c=0; c<COLS; c++)
        {
            if (c == 0 || c == COLS-1)
                mGrid[r][c] = '#';
            else
                mGrid[r][c] = ' ';
        }
    }

    //add snake to mGrid
    mHead = new Snake(ROWS/2 + 1, COLS/2, 'R', nextChar());
    snake.push_back(mHead);
    lenSnake++;

    growSnake();
    growSnake();
    
    //add mFruit to mGrid
    spawnFruit();
    
    update();
    draw();
    cout << "Tap arrow keys to change directions";
    getCharacter();
}

void Arena::redrawBounds()
{
    //re-draw top and bottom walls
    for (int c=0; c<COLS; c++)
    {
        mGrid[0][c] = '#';
        mGrid[ROWS-1][c] = '#';
    }
    
    //redraw left and right walls
    for (int r=1; r<ROWS-1; r++)
    {
        for (int c=0; c<COLS; c++)
        {
            if (c == 0 || c == COLS-1)
                mGrid[r][c] = '#';
        }
    }
}

//update snake position, mFruit position in mGrid
void Arena::update()
{
    bool spawnfruit = false;
    
    //move snake
    moveSnake();
    
    if (mGrid[mHead->row()][mHead->col()] == '#')
        mGameOver = true;
    
    //check if head has run into body
    for (int s = 1; s < lenSnake; s++)
    {
        if (mHead->row() == snake[s]->row() && mHead->col() == snake[s]->col())
            mGameOver = true;
    }
    
    //check if head is touching food
    if (mHead->row() == mFruit->row() && mHead->col() == mFruit->col())
    {
        spawnfruit = true;
        mScore++;
        
        //grow
        growSnake();
    }
    
    //check if player won
    if (lenSnake >= ((ROWS - 2 - 2*SPAWNDIST)*((COLS-1)/2 - 4*SPAWNDIST)))
        setGameWon();
    
    updateSnake();
    
    //redraw boundary
    redrawBounds();
    
    //spawn fruit
    if (spawnfruit)
        spawnFruit();
}

//draw mGrid onto console (walls, snake, mFruit)
void Arena::draw()
{
    clearScreen();
    cout << "(p)ause        (q)uit" << endl;
    for (int r=0; r<ROWS; r++)
    {
        for (int c=0; c< COLS; c++)
        {
            cout << mGrid[r][c];
        }
        cout << endl;
    }
    cout << "Score: " << mScore << endl;
}

//Accessors
Snake* Arena::head() const
{
    return mHead;
}

bool Arena::gameOver() const
{
    return mGameOver;
}

bool Arena::gameWon() const
{
    return mGameWon;
}

char Arena::nextChar() const
{
    if (lenSnake < STR.size())
        return STR[lenSnake];
    else
        return 'O';
}

//Mutators
void Arena::spawnFruit()
{
    int randR, randC;
    randR = randInt(1+SPAWNDIST, ROWS-2-SPAWNDIST);
    do
    {
        randC = randInt(1+SPAWNDIST, COLS-2-SPAWNDIST);
    } while (mGrid[randR][randC] != ' ' || (randC % 2 == 0));
    
    delete mFruit;
    mFruit = new Fruit(randR, randC);
    mGrid[randR][randC] = mFruit->symbol();
}

void Arena::growSnake()
{
    char lastDir = snake[lenSnake - 1]->dir();  //direction of the snake tail object
    int newRow = snake[lenSnake - 1]->row();
    int newCol = snake[lenSnake - 1]->col();
    
    switch (lastDir)
    {
        case 'U':
        {
            newRow++;
            break;
        }
            
        case 'D':
        {
            newRow--;
            break;
        }
            
        case 'L':
        {
            newCol+=2;
            break;
        }
            
        case 'R':
        {
            newCol-=2;
            break;
        }
    }
    
    Snake* s = new Snake(newRow, newCol, lastDir, nextChar());
    snake.push_back(s);
    lenSnake++;
}

void Arena::moveSnake()
{
    for (int s = 0; s < lenSnake; s++)
    {
        Snake* obj = snake[s];
        int row = obj->row();
        int col = obj->col();
        char dir = obj->dir();
        
        mGrid[row][col] = ' ';
        
        switch (dir)
        {
            case 'U':
            {
                obj->setRow(row - ROWSPEED);
                break;
            }
            case 'D':
            {
                obj->setRow(row + ROWSPEED);
                break;
            }
            case 'L':
            {
                obj->setCol(col - COLSPEED);
                break;
            }
            case 'R':
            {
                obj->setCol(col + COLSPEED);
                break;
            }
        }
        
        //if at the edge, appear at other side
        if (row <= 1 && dir == 'U')
        {
            obj->setRow(ROWS - 2);
        }
        if (row >= ROWS - 2 && dir == 'D')
        {
            obj->setRow(1);
        }
        if (col <= 1 && dir == 'L')
        {
            obj->setCol(COLS - 2);
        }
        if (col >= COLS - 2 && dir == 'R')
        {
            obj->setCol(1);
        }
    }
}

void Arena::updateSnake()
{
    int prevDir = mHead->dir();
    
    for (int s = 0; s < lenSnake; s++)
    {
        Snake* obj = snake[s];
        int newRow = obj->row();
        int newCol = obj->col();
        mGrid[newRow][newCol] = obj->symbol();
        
        //set mDir of current obj to mDir of prev obj in the vector
        char temp = obj->dir();
        obj->setDir(prevDir);
        prevDir = temp;
    }
    //re-draw head
    mGrid[snake[0]->row()][snake[0]->col()] = snake[0]->symbol();
}

void Arena::setGameOver()
{
    mGameOver = true;
}

void Arena::setGameWon()
{
    mGameWon = true;
}

//destructor
Arena::~Arena()
{
    //delete snake objects
    for (int i = 0; i < lenSnake; i++)
    {
        delete snake[i];
    }
    
    //delete fruit object
    delete mFruit;
}


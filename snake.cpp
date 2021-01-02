//
//  snake.cpp
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#include "snake.h"

Snake::Snake(int r, int c, char d, char s) :
mRow(r),
mCol(c),
mDir(d),
mSymbol(s)
{}

//Accessors
int Snake::row() const
{
    return mRow;
}

int Snake::col() const
{
    return mCol;
}

char Snake::dir() const
{
    return mDir;
}

char Snake::symbol() const
{
    return mSymbol;
}

//Mutators
void Snake::setRow(int r)
{
    mRow = r;
}

void Snake::setCol(int c)
{
    mCol = c;
}

void Snake::setDir(char d)
{
    switch (d)
    {
        case 'U':
        {
            if (mDir != 'D')
                mDir = 'U';
            break;
        }
        case 'D':
        {
            if (mDir != 'U')
                mDir = 'D';
            break;
        }
        case 'L':
        {
            if (mDir != 'R')
                mDir = 'L';
            break;
        }
        case 'R':
        {
            if (mDir != 'L')
                mDir = 'R';
            break;
        }
    }
}



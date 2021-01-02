//
//  fruit.cpp
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#include "fruit.h"
#include "utilities.h"

Fruit::Fruit(int r, int c) :
mRow(r),
mCol(c),
mSymbol('*')
{}

//accessors
int Fruit::row() const
{
    return mRow;
}

int Fruit::col() const
{
    return mCol;
}

char Fruit::symbol() const
{
    return mSymbol;
}


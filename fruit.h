//
//  fruit.h
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#ifndef fruit_h
#define fruit_h

class Fruit
{
public:
    Fruit(int r, int c);
    
    //Accessors
    int row() const;
    int col() const;
    char symbol() const;
    
private:
    int mRow;
    int mCol;
    char mSymbol;
};

#endif /* fruit_h */

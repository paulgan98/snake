//
//  snake.h
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#ifndef snake_h
#define snake_h

class Snake
{
public:
    Snake(int r, int c, char d, char s);
    
    //Accessors
    int row() const;
    int col() const;
    char dir() const;
    char symbol() const;
   
    //Mutators
    void setRow(int r);
    void setCol(int c);
    void setDir(char d);
    
private:
    int mRow;
    int mCol;
    char mDir;
    char mSymbol;
};

#endif /* snake_h */

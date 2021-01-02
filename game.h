//
//  game.h
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#ifndef game_h
#define game_h
#include <string>

class Arena;
class Snake;
class Game
{
public:
    Game();
    
    void play();
    void getInput();
    
    ~Game();
    
private:
    Arena* mArena;
    Snake* mHead;
//    bool gameOver;
};

#endif /* game_h */

//
//  game.cpp
//  newSnake
//
//  Created by Paul G on 7/3/20.
//  Copyright © 2020 Paul G. All rights reserved.
//

#include "game.h"
#include "arena.h"
#include "snake.h"
#include "utilities.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

Game::Game() :
mArena(new Arena),
mHead(mArena->head())
{}

void Game::play()
{
    while (!mArena->gameOver() && !mArena->gameWon())
    {
        getInput();
        mArena->update();
        mArena->draw();
        usleep(111111);
    }
    
    if (mArena->gameWon() && !mArena->gameOver())
        cout << "You Win!" << endl;
    else if (mArena->gameOver() && !mArena->gameWon())
        cout << "Game Over" << endl;
}

//get keyboard inputs
void Game::getInput()
{
    if (kbhit())
    {
        char c = getCharacter();
        switch (c)
        {
            case 'q':
            {
                mArena->setGameOver();
                mArena->setGameWon();
                break;
            }
            case 'p':
            {
                cout << "Press any key to resume.";
                getCharacter();
                break;
            }
            case ARROW_UP:
            {
                mHead->setDir('U');
                break;
            }
            case ARROW_DOWN:
            {
                mHead->setDir('D');
                break;
            }
            case ARROW_LEFT:
            {
                mHead->setDir('L');
                break;
            }
            case ARROW_RIGHT:
            {
                mHead->setDir('R');
                break;
            }
        }
    }
}

Game::~Game()
{
    delete mArena;
}

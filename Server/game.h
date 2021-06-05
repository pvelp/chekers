#ifndef GAME_H
#define GAME_H
#include "header.h"

enum Player{NONE, black, white};

typedef struct Game
{
    enum Player currentPlayer;
    bool isSurrender;
    bool Direction;
    void (*switchPlayer)(struct Game *self);
} Game ;

struct Game *newGame();
bool getDirection (struct Game *self);
void switchPlayer(struct Game *self);

enum CurrentState{
    WaitMove,
    MakeMove,
    GameOver
};


#endif

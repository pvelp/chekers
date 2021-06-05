#include "game.h"
#include <stdlib.h>
#include <stdio.h>

Game *newGame(){

    Game *game = (Game*)malloc(sizeof (Game));
    if (!game){
        return NULL;
    }
    game->currentPlayer = white;
    game->switchPlayer = switchPlayer;
    game->Direction = false;
    game->isSurrender = false;

    return game;
}

void switchPlayer(struct Game *self){
    if (self->currentPlayer == white){
        self->currentPlayer = black;
        self->Direction = true;
    } else {
        self->currentPlayer = white;
        self->Direction = false;
    }
}

void clear(){
    printf("\033[2J");
    printf("\033[0;0f");
}


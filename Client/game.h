#ifndef GAME_H
#define GAME_H
#include "header.h"

enum Player{NONE, black, white, winner, loser};
typedef struct Game
{
    int score;
    int enemy_score;
    enum Player lastPlayer;
    bool isSurrender;
    bool Direction;
    int Winner;
} Game ;


struct Game *newGame();


enum Combat{
    ShouldCombat,
    None,
};

enum CurrentState{
    WaitMove,
    MakeMove,
    Surrener,
    WIN,
    LOSE
};

bool queen_should_combar_after_our_move(struct Board *board, struct Position *last_our_position);
bool queen_should_combat_after_enemy_move(struct Board *board, struct Position *last_enemy_position);
bool shouldCombat_after_enemy_move (struct Board *board, struct Position *last_enemy_move);
bool shouldCombat_after_our_move(struct Board *board, struct Position *last_our_position);
bool can_combat_after_reales(Board *board, struct Position *startPosition);

bool is_surrender(struct MovePosition position);
bool set_combat_flag(Board *board, struct MovePosition position);

#endif

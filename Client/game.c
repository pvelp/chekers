#include "game.h"
#include <stdlib.h>
#include <stdio.h>

Game *newGame(){

    Game *game = (Game*)malloc(sizeof (Game));
    if (!game){
        return NULL;
    }
    struct Board *board;
    board = newBoard();
    game->lastPlayer = white;
    game->Direction = false;
    game->isSurrender = false;

    return game;
}

bool queen_should_combar_after_our_move(struct Board *board, struct Position *last_our_position){
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    bool res4 = false;
    bool res = false;
    Position pos1, pos2, pos3, pos4, pos_after;
    pos1 = *last_our_position;
    pos2 = *last_our_position;
    pos3 = *last_our_position;
    pos4 = *last_our_position;
    if (board->cells[findCell(board, last_our_position)].isQueen){
        while (pos1.x != 7 && pos1.y != 7) {
            pos1.x++;
            pos1.y++;
            if (board->cells[findCell(board, &pos1)].color == board->cells[findCell(board, last_our_position)].color){
                break;
            }
            if (board->cells[findCell(board, &pos1)].color != board->cells[findCell(board, last_our_position)].color
                    && board->cells[findCell(board, &pos1)].color != BLANK){
                pos_after = pos1;
                pos_after.x++;
                pos_after.y++;
                if (board->cells[findCell(board, &pos_after)].color == BLANK){
                    res1 = true;
                    break;
                } else {
                    break;
                }
            }
        }

        while (pos2.x != 0 && pos2.y != 0) {
            pos2.x--;
            pos2.y--;
            if (board->cells[findCell(board, &pos2)].color == board->cells[findCell(board, last_our_position)].color){
                break;
            }
            if (board->cells[findCell(board, &pos2)].color != board->cells[findCell(board, last_our_position)].color
                    && board->cells[findCell(board, &pos2)].color != BLANK){
                pos_after = pos2;
                pos_after.x--;
                pos_after.y--;
                if (board->cells[findCell(board, &pos_after)].color == BLANK){
                    res2 = true;
                    break;
                } else {
                    break;
                }
            }
        }


        while (pos3.x != 7 && pos3.y != 0) {
            pos3.x++;
            pos3.y--;
            if (board->cells[findCell(board, &pos3)].color == board->cells[findCell(board, last_our_position)].color){
                break;
            }
            if (board->cells[findCell(board, &pos3)].color != board->cells[findCell(board, last_our_position)].color
                    && board->cells[findCell(board, &pos3)].color != BLANK){
                pos_after = pos3;
                pos_after.x++;
                pos_after.y--;
                if (board->cells[findCell(board, &pos_after)].color == BLANK){
                    res3 = true;
                    break;
                } else {
                    break;
                }
            }
        }

        while (pos4.x != 0 && pos4.y != 7) {
            pos4.x--;
            pos4.y++;
            if (board->cells[findCell(board, &pos4)].color == board->cells[findCell(board, last_our_position)].color){
                break;
            }
            if (board->cells[findCell(board, &pos4)].color != board->cells[findCell(board, last_our_position)].color
                    && board->cells[findCell(board, &pos4)].color != BLANK){
                pos_after = pos4;
                pos_after.x--;
                pos_after.y++;
                if (board->cells[findCell(board, &pos_after)].color == BLANK){
                    res4 = true;
                    break;
                } else {
                    break;
                }
            }
        }
    }
    if (res1 || res2 || res3 || res4){
        res = true;
    }
    return res;
}

bool queen_should_combat_after_enemy_move(struct Board *board, struct Position *last_enemy_position){
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    bool res4 = false;
    bool res = false;
    Position pos1, pos2, pos3, pos4, pos_before;
    pos1 = *last_enemy_position;
    pos2 = *last_enemy_position;
    pos3 = *last_enemy_position;
    pos4 = *last_enemy_position;

    while (pos1.x != 7 && pos1.y != 7) {
        pos1.x++;
        pos1.y++;
        if (board->cells[findCell(board, &pos1)].color == board->cells[findCell(board, last_enemy_position)].color){
            break;
        }
        if (board->cells[findCell(board, &pos1)].color != board->cells[findCell(board, last_enemy_position)].color
                && board->cells[findCell(board, &pos1)].color != BLANK
                && board->cells[findCell(board, &pos1)].isQueen == true){
            pos_before = *last_enemy_position;
            pos_before.x--;
            pos_before.y--;
            if (board->cells[findCell(board, &pos_before)].color == BLANK){
                res1 = true;
                break;
            }
        }
    }

    while (pos2.x != 0 && pos2.y != 0) {
        pos2.x--;
        pos2.y--;
        if (board->cells[findCell(board, &pos2)].color == board->cells[findCell(board, last_enemy_position)].color){
            break;
        }
        if (board->cells[findCell(board, &pos2)].color != board->cells[findCell(board, last_enemy_position)].color
                && board->cells[findCell(board, &pos2)].color != BLANK
                && board->cells[findCell(board, &pos2)].isQueen == true){
            pos_before = *last_enemy_position;
            pos_before.x++;
            pos_before.y++;
            if (board->cells[findCell(board, &pos_before)].color == BLANK){
                res2 = true;
                break;
            }
        }
    }


    while (pos3.x != 7 && pos3.y != 0) {
        pos3.x++;
        pos3.y--;
        if (board->cells[findCell(board, &pos3)].color == board->cells[findCell(board, last_enemy_position)].color){
            break;
        }
        if (board->cells[findCell(board, &pos3)].color != board->cells[findCell(board, last_enemy_position)].color
                && board->cells[findCell(board, &pos3)].color != BLANK
                && board->cells[findCell(board, &pos3)].isQueen == true){
            pos_before = *last_enemy_position;
            pos_before.x--;
            pos_before.y++;
            if (board->cells[findCell(board, &pos_before)].color == BLANK){
                res3 = true;
                break;
            }
        }
    }

    while (pos4.x != 0 && pos4.y != 7) {
        pos4.x--;
        pos4.y++;
        if (board->cells[findCell(board, &pos4)].color == board->cells[findCell(board, last_enemy_position)].color){
            break;
        }
        if (board->cells[findCell(board, &pos4)].color != board->cells[findCell(board, last_enemy_position)].color
                && board->cells[findCell(board, &pos4)].color != BLANK
                && board->cells[findCell(board, &pos4)].isQueen == true){
            pos_before = *last_enemy_position;
            pos_before.x++;
            pos_before.y--;
            if (board->cells[findCell(board, &pos_before)].color == BLANK){
                res4 = true;
                break;
            }
        }
    }
    if (res1 || res2 || res3 || res4){
        res = true;
    }
    return res;
}

bool shouldCombat_after_enemy_move (struct Board *board, struct Position *last_enemy_move){
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    bool res4 = false;
    bool res = false;

    Position ourPosition1, ourPosition2, ourPosition3, ourPosition4;
    Position target_position1, target_position2, target_position3, target_position4;

    ourPosition1.x = last_enemy_move->x + 1;
    ourPosition1.y = last_enemy_move->y + 1;

    ourPosition2.x = last_enemy_move->x + 1;
    ourPosition2.y = last_enemy_move->y - 1;

    ourPosition3.x = last_enemy_move->x - 1;
    ourPosition3.y = last_enemy_move->y + 1;

    ourPosition4.x = last_enemy_move->x - 1;
    ourPosition4.y = last_enemy_move->y - 1;

    target_position1.x = last_enemy_move->x-1;
    target_position1.y = last_enemy_move->y-1;

    target_position2.x = last_enemy_move->x-1;
    target_position2.y = last_enemy_move->y+1;

    target_position3.x = last_enemy_move->x+1;
    target_position3.y = last_enemy_move->y-1;

    target_position4.x = last_enemy_move->x+1;
    target_position4.y = last_enemy_move->y+1;

    int enemyColor = board->cells[findCell(board, last_enemy_move)].color;;
    int targetColor;
    int currentColor;

    if (target_position1.x >= 0 && target_position1.x <= 7 && target_position1.y >= 0 && target_position1.y <= 7){
        targetColor = board->cells[findCell(board, &target_position1)].color;
        currentColor = board->cells[findCell(board, &ourPosition1)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res1 = true;
        }
    }

    if (target_position2.x >= 0 && target_position2.x <= 7 && target_position2.y >= 0 && target_position2.y <= 7){
        targetColor = board->cells[findCell(board, &target_position2)].color;
        currentColor = board->cells[findCell(board, &ourPosition2)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res2 = true;
        }
    }

    if (target_position3.x >= 0 && target_position3.x <= 7 && target_position3.y >= 0 && target_position3.y <= 7){
        targetColor = board->cells[findCell(board, &target_position3)].color;
        currentColor = board->cells[findCell(board, &ourPosition3)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res3 = true;
        }
    }

    if (target_position4.x >= 0 && target_position4.x <= 7 && target_position4.y >= 0 && target_position4.y <= 7){
        targetColor = board->cells[findCell(board, &target_position4)].color;
        currentColor = board->cells[findCell(board, &ourPosition4)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res4 = true;
        }
    }
    if (res1 || res2 || res3 || res4 || queen_should_combat_after_enemy_move(board, last_enemy_move)){
        res = true;
    }
    return res;
}

bool shouldCombat_after_our_move(struct Board *board, struct Position *last_our_position){
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    bool res4 = false;
    bool res = false;
    Position enemyPosition1, enemyPosition2, enemyPosition3, enemyPosition4;
    Position target_position1, target_position2, target_position3, target_position4;

    enemyPosition1.x = last_our_position->x + 1;
    enemyPosition1.y = last_our_position->y + 1;

    enemyPosition2.x = last_our_position->x + 1;
    enemyPosition2.y = last_our_position->y - 1;

    enemyPosition3.x = last_our_position->x - 1;
    enemyPosition3.y = last_our_position->y + 1;

    enemyPosition4.x = last_our_position->x - 1;
    enemyPosition4.y = last_our_position->y - 1;

    target_position1.x = enemyPosition1.x + 1;
    target_position1.y = enemyPosition1.y + 1;

    target_position2.x = enemyPosition2.x + 1;
    target_position2.y = enemyPosition2.y - 1;

    target_position3.x = enemyPosition3.x - 1;
    target_position3.y = enemyPosition3.y + 1;

    target_position4.x = enemyPosition4.x - 1;
    target_position4.y = enemyPosition4.y - 1;


    int currentColor = board->cells[findCell(board, last_our_position)].color;
    int targetColor, enemyColor;

    if (target_position1.x >= 0 && target_position1.x <= 7 && target_position1.y >= 0 && target_position1.y <= 7){
        targetColor = board->cells[findCell(board, &target_position1)].color;
        enemyColor = board->cells[findCell(board, &enemyPosition1)].color;
        if (targetColor == BLANK && enemyColor != BLANK && currentColor != BLANK && currentColor != enemyColor){
            res1 = true;
        }
    }

    if (target_position2.x >= 0 && target_position2.x <= 7 && target_position2.y >= 0 && target_position2.y <= 7){
        targetColor = board->cells[findCell(board, &target_position2)].color;
        enemyColor = board->cells[findCell(board, &enemyPosition2)].color;
        if (targetColor == BLANK && enemyColor != BLANK && currentColor != BLANK && currentColor != enemyColor){
            res2 = true;
        }
    }

    if (target_position3.x >= 0 && target_position3.x <= 7 && target_position3.y >= 0 && target_position3.y <= 7){
        targetColor = board->cells[findCell(board, &target_position3)].color;
        enemyColor = board->cells[findCell(board, &enemyPosition3)].color;
        if (targetColor == BLANK && enemyColor != BLANK && currentColor != BLANK && currentColor != enemyColor){
            res3 = true;
        }
    }

    if (target_position4.x >= 0 && target_position4.x <= 7 && target_position4.y >= 0 && target_position4.y <= 7){
        targetColor = board->cells[findCell(board, &target_position4)].color;
        enemyColor = board->cells[findCell(board, &enemyPosition4)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res4 = true;
        }
    }
    if (res1 || res2 || res3 || res4 || queen_should_combar_after_our_move(board, last_our_position)){
        res = true;
    }
    return res;

}

bool can_combat_after_reales(Board *board, struct Position *startPosition){
    bool res1 = false;
    bool res2 = false;
    bool res3 = false;
    bool res4 = false;
    bool res = false;
    Position enemyPosition1, enemyPosition2, enemyPosition3, enemyPosition4;
    Position ourPosition1, ourPosition2, ourPosition3, ourPosition4;

    enemyPosition1.x = startPosition->x + 1;
    enemyPosition1.y = startPosition->y + 1;

    enemyPosition2.x = startPosition->x + 1;
    enemyPosition2.y = startPosition->y - 1;

    enemyPosition3.x = startPosition->x - 1;
    enemyPosition3.y = startPosition->y + 1;

    enemyPosition4.x = startPosition->x - 1;
    enemyPosition4.y = startPosition->y - 1;

    ourPosition1.x = enemyPosition1.x + 1;
    ourPosition1.y = enemyPosition1.y + 1;

    ourPosition2.x = enemyPosition2.x + 1;
    ourPosition2.y = enemyPosition2.y - 1;

    ourPosition3.x = enemyPosition3.x - 1;
    ourPosition3.y = enemyPosition3.y + 1;

    ourPosition4.x = enemyPosition4.x - 1;
    ourPosition4.y = enemyPosition4.y - 1;

    int currentColor;
    int enemyColor;
    int targetColor = BLANK;


    if (ourPosition1.x >= 0 && ourPosition1.x <= 7 && ourPosition1.y >= 0 && ourPosition1.y <= 7){
        enemyColor = board->cells[findCell(board, &enemyPosition1)].color;
        currentColor = board->cells[findCell(board, &ourPosition1)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res1 = true;
        }
    }

    if (ourPosition2.x >= 0 && ourPosition2.x <= 7 && ourPosition2.y >= 0 && ourPosition2.y <= 7){
        enemyColor = board->cells[findCell(board, &enemyPosition2)].color;
        currentColor = board->cells[findCell(board, &ourPosition2)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res2 = true;
        }
    }

    if (ourPosition3.x >= 0 && ourPosition3.x <= 7 && ourPosition3.y >= 0 && ourPosition3.y <= 7){
        enemyColor = board->cells[findCell(board, &enemyPosition3)].color;
        currentColor = board->cells[findCell(board, &ourPosition3)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res3 = true;
        }
    }

    if (ourPosition4.x >= 0 && ourPosition4.x <= 7 && ourPosition4.y >= 0 && ourPosition4.y <= 7){
        enemyColor = board->cells[findCell(board, &enemyPosition4)].color;
        currentColor = board->cells[findCell(board, &ourPosition4)].color;
        if (enemyColor != targetColor && currentColor != enemyColor && currentColor != targetColor && targetColor == BLANK){
            res4 = true;
        }
    }
    if (res1 || res2 || res3 || res4){
        res = true;
    }
    return res;
}

bool is_surrender(struct MovePosition position){
    bool res = false;
    if (position.startPosition.x == 0 &&
            position.startPosition.y == 0 &&
            position.endPosition.x == 0 &&
            position.endPosition.y == 0){
        res = true;
    }
    return res;
}

bool set_combat_flag(Board *board, struct MovePosition position){
    bool res = false;
    bool combat_flag_after_reales = false;
    bool combat_flag_after_enemy_move = false;

    if (can_combat_after_reales(board, &position.startPosition)){
        combat_flag_after_reales = true;
    } else {
        combat_flag_after_reales = false;
    }
    if (shouldCombat_after_enemy_move(board, &position.endPosition) == true){
        combat_flag_after_enemy_move = true;
    } else {
        combat_flag_after_enemy_move = false;
    }
    if (combat_flag_after_enemy_move || combat_flag_after_reales){
        res = true;
    } else {
        res = false;
    }
    return res;
}


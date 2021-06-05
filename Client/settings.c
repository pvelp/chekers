#include "header.h"

void settings(NetworkContext *ctx, Board *board, int *state, bool *direction, int *color, int *enemy_color){
    char buffer[MAXLINE];
    char name[MAXLINE];
    int queue = add_player(ctx, name, buffer, board);
    if (queue == 1){
        *state = MakeMove;
        *direction = false;
        *color = white;
        *enemy_color = black;
        printf("       Вы играете за белых\n");
    } else {
        *state = WaitMove;
        *direction = true;
        *color = black;
        *enemy_color = white;
        printf("       Вы играете за черных\n");
        printf(MOD "Ход другого игрока" STOP "\n");
    }
}

void clear(){
    printf("\033[2J");
    printf("\033[0;0f");
}

unsigned short update_score(unsigned short score, int move_result){
    if (move_result == SUCCESSFUL_COMBAT){
        score++;
    }
    return score;
}

void display_game_info(Board *board, unsigned short score, unsigned short enemy_score, int color){
    clear();
    if (color == white){
        printf(MOD "                                              Вы играете за БЕЛЫХ" STOP "\n");
    } else {
        printf(MOD "                                              Вы играете за ЧЕРНЫХ" STOP "\n");
    }
    print_board(board);
    printf("Ваш счет: %d\nСчет соперника: %d\n\n", score, enemy_score);
}

void print_results(Board *board, unsigned short score, unsigned short enemy_score, int state){
    clear();
    print_board(board);
    print_score(score, enemy_score);
    if (state == Surrener){
        printf("Вы сдались! Конец игры\n");
    }
    if (state == WIN){
        printf("Вы победили! Конец игры\n");
    }
    if (state == LOSE){
        printf("Вы проиграли! Конец игры!\n");
    }
}

void print_score(unsigned short score, unsigned short enemy_score){
    printf("Ваш счет: %d\nСчет соперника: %d\n\n", score, enemy_score);
}

void set_states_after_our_move(Board *board, Message *msg, bool *combat_flag_after_our_move, int *state, int score, int enemy_score, int color){
    if (shouldCombat_after_our_move(board, &msg->move_position.endPosition) && !msg->isSurrender){
        *combat_flag_after_our_move = true;
        display_game_info(board, score, enemy_score, color);
        msg->type = CombatAgain;
        *state = MakeMove;
    } else {
        *combat_flag_after_our_move = false;
        display_game_info(board, score, enemy_score, color);
        msg->type = Default;
        *state = WaitMove;
    }
}

void print_enemy_move(Message msg){
    printf("Ход другого игрока получен, %d %d %d %d\n",
           msg.move_position.startPosition.x,
           msg.move_position.startPosition.y,
           msg.move_position.endPosition.x,
           msg.move_position.endPosition.y);
}

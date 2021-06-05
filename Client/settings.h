#ifndef SETTINGS_H
#define SETTINGS_H
#include "header.h"
#include "protocol.h"

void settings(struct _NetworkContext *ctx, Board *board, int *state, bool *direction, int *color, int *enemy_color);
unsigned short update_score(unsigned short score, int move_result);
void display_game_info(Board *board, unsigned short score, unsigned short enemy_score, int color);
void print_score(unsigned short score, unsigned short enemy_score);
void print_results(Board *board, unsigned short score, unsigned short enemy_score, int state);
void set_states_after_our_move(Board *board, struct Message *msg, bool *combat_flag_after_our_move, int *state, int score, int enemy_score, int color);
void print_enemy_move(struct Message msg);

#endif // SETTINGS_H

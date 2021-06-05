#ifndef SETTINGS_H
#define SETTINGS_H
#include "header.h"

void sign_in(NetworkContext *ctx, sockaddr_in *playerWhite_addr, sockaddr_in *playerBlack_addr);
void send_settings(NetworkContext *ctx, sockaddr_in playerWhite_addr, sockaddr_in playerBlack_addr);
void print_msg_move_form_client(Message msg);
void print_msg_move_for_client(Message msg);
void display_game_info(Board *board, unsigned short white_score, unsigned short black_score, struct Game *gamestate);

#endif // SETTINGS_H

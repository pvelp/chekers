#include "header.h"

int main() {

    int color, enemy_color, state, move_result, n;
    bool direction;

    unsigned short score = 0;
    unsigned short enemy_score = 0;

    NetworkContext *network_context = network_init(PORT, INADDR_LOOPBACK);
    Board *board = newBoard();
    Game *game_state = newGame();

    bool combat_flag_after_our_move = false;
    bool combat_flag = false;

    reset_map(board);
    settings(network_context, board, &state, &direction, &color, &enemy_color);

    while (game_state->Winner == NONE) {
        Message message_for_server;
        switch (state) {
        case MakeMove:
            move_result = PROHIBITED;
            if (combat_flag || combat_flag_after_our_move){
                while (move_result != SUCCESSFUL_COMBAT) {
                    printf("ВЫ ДОЛЖНЫ СЪЕСТЬ!\n");
                    message_for_server.move_position = getMove();
                    if (is_surrender(message_for_server.move_position)){
                        message_for_server.isSurrender = true;
                        sendto_server_move(network_context, message_for_server);
                        state = Surrener;
                        break;
                    }

                    message_for_server.direction = direction;
                    move_result = validMove(board,
                                            &message_for_server.move_position.startPosition,
                                            &message_for_server.move_position.endPosition,
                                            direction,
                                            color);
                }

                move_result = makeMove(board,
                                       &message_for_server.move_position.startPosition,
                                       &message_for_server.move_position.endPosition,
                                       direction,
                                       color);
                score = update_score(score, move_result);
                message_for_server.score = score;

                if (score == 12){
                    message_for_server.type = GameOver;
                    state = WIN;
                    sendto_server_move(network_context, message_for_server);
                    break;
                }

                set_states_after_our_move(board, &message_for_server, &combat_flag_after_our_move, &state, score, enemy_score, color);
                sendto_server_move(network_context, message_for_server);
                combat_flag = false;

                if (combat_flag_after_our_move && !message_for_server.isSurrender){
                    while (move_result != SUCCESSFUL_COMBAT) {
                        printf("ВЫ ДОЛЖНЫ СЪЕСТЬ!\n");
                        message_for_server.move_position = getMove();
                        if (is_surrender(message_for_server.move_position)){
                            message_for_server.isSurrender = true;
                            sendto_server_move(network_context, message_for_server);
                            state = Surrener;
                            break;
                        }
                        message_for_server.direction = direction;
                        move_result = validMove(board,
                                                &message_for_server.move_position.startPosition,
                                                &message_for_server.move_position.endPosition,
                                                direction,
                                                color);
                    }
                    move_result = makeMove(board,
                                           &message_for_server.move_position.startPosition,
                                           &message_for_server.move_position.endPosition,
                                           direction,
                                           color);

                    score = update_score(score, move_result);
                    message_for_server.score = score;
                    if (score == 12){
                        message_for_server.type = GameOver;
                        state = WIN;
                        sendto_server_move(network_context, message_for_server);
                        break;
                    }

                    set_states_after_our_move(board, &message_for_server, &combat_flag_after_our_move, &state, score, enemy_score, color);
                    sendto_server_move(network_context, message_for_server);

                } else {
                    if (message_for_server.isSurrender){
                        state = Surrener;
                        break;
                    } else{
                        printf(MOD "Ход другого игрока" STOP "\n");
                    }
                }
            } else {
                while (move_result == PROHIBITED){
                    message_for_server.move_position = getMove();
                    if (is_surrender(message_for_server.move_position)){
                        message_for_server.isSurrender = true;
                        sendto_server_move(network_context, message_for_server);
                        state = Surrener;
                        break;
                    }

                    message_for_server.direction = direction;
                    move_result = validMove(board,
                                            &message_for_server.move_position.startPosition,
                                            &message_for_server.move_position.endPosition,
                                            direction,
                                            color);
                }

                move_result = makeMove(board,
                                       &message_for_server.move_position.startPosition,
                                       &message_for_server.move_position.endPosition,
                                       direction,
                                       color);

                score = update_score(score, move_result);
                message_for_server.score = score;
                if (score == 12){
                    message_for_server.type = GameOver;
                    state = WIN;
                    sendto_server_move(network_context, message_for_server);
                    break;
                }

                if (move_result == SUCCESSFUL_COMBAT){
                    if (shouldCombat_after_our_move(board, &message_for_server.move_position.endPosition)){
                        combat_flag_after_our_move = true;
                        state = MakeMove;
                    } else {
                        combat_flag_after_our_move = false;
                        state = WaitMove;
                    }
                }

                if(message_for_server.isSurrender){
                    state = Surrener;
                } else {
                    state = WaitMove;
                    message_for_server.type = Default;
                    sendto_server_move(network_context, message_for_server);
                    display_game_info(board, score, enemy_score, color);
                    printf(MOD "Ход другого игрока" STOP "\n");
                }
            }
            break;

        case WaitMove:
        {
            Message msg;
            n = network_recv(network_context, &msg, sizeof (msg));
            enemy_score = msg.score;
            if (msg.isSurrender == true){
                state = WIN;
                break;
            } else {
                move_result = makeMove(board,
                                       &msg.move_position.startPosition,
                                       &msg.move_position.endPosition,
                                       msg.direction,
                                       enemy_color);
                display_game_info(board, score, enemy_score, color);
                print_enemy_move(msg);

                combat_flag = set_combat_flag(board, msg.move_position);

                if (msg.type == Default){
                    state = MakeMove;
                } else if (msg.type == GameOver){
                    state = LOSE;
                    break;
                } else {
                    state = WaitMove;
                    printf(MOD "Ход другого игрока" STOP "\n");
                }
            }
            break;
        }
        case Surrener:
            game_state->Winner = loser;
            print_results(board, score, enemy_score, state);
            break;
        case WIN:
            game_state->Winner = winner;
            print_results(board, score, enemy_score, state);
            break;
        case LOSE:
            game_state->Winner = loser;
            print_results(board, score, enemy_score, state);
            break;
        }
    }
    close(network_context->sock);
    free(network_context);
    return 0;
}

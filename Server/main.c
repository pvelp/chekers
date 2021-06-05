#include "header.h"

int main() {
    sockaddr_in playerWhite_addr, playerBlack_addr;

    struct Game *game_state = newGame();
    struct Board *board = newBoard();

    Message msg;
    Message msg_for_client;

    unsigned short white_score = 0;
    unsigned short black_score = 0;

    int len_whitePlayer, len_blackPlayer, move_result, n;

    board->resetMap(board);
    NetworkContext *network_context = network_init(PORT);

    if (!network_context) {
        printf("Ошибка инициализации сети\n");
        return -1;
    }

    memset(&playerWhite_addr, 0, sizeof(playerWhite_addr));
    memset(&playerBlack_addr, 0, sizeof(playerBlack_addr));

    len_whitePlayer = sizeof (playerWhite_addr);
    len_blackPlayer = sizeof (playerBlack_addr);

    // получаем имя и запоминаем адреса
    sign_in(network_context, &playerWhite_addr, &playerBlack_addr);
    // уведомить за кого играют клиенты
    send_settings(network_context, playerWhite_addr, playerBlack_addr);

    // вывод доски
    print_board(board);


    while (1){

        if (game_state->currentPlayer == white){
            n = recvfrom(network_context->sock,
                         &msg,
                         sizeof(msg),
                         MSG_WAITALL,
                         (struct sockaddr *) &playerWhite_addr,
                         &len_whitePlayer);

            if (n == sizeof (msg)){
                print_msg_move_form_client(msg);
                move_result = board->makeMove(board,
                                              &msg.move_position.startPosition,
                                              &msg.move_position.endPosition,
                                              msg.direction,
                                              white);
                white_score = msg.score;
                msg_for_client = msg;
                msg_for_client.score = white_score;
                sendto(network_context->sock,
                       &msg_for_client,
                       sizeof (msg_for_client),
                       0,
                       (const struct sockaddr *) &playerBlack_addr,
                       len_blackPlayer);

                display_game_info(board, white_score, black_score, game_state);

                if (msg.isSurrender == true){
                    printf("Белые сдались! Конец игры!\n");
                    break;
                }
                if (white_score == 12){
                    printf("Конец игры!\n");
                    break;
                }
                print_msg_move_for_client(msg_for_client);
            } else {
                printf("Пакет не дошел\n");
            }
            if (msg.type == Default){
                game_state->switchPlayer(game_state);
            } else {
                continue;
            }
        }

        if (game_state->currentPlayer == black){
            n = recvfrom(network_context->sock,
                         &msg,
                         sizeof(msg),
                         MSG_WAITALL,
                         (struct sockaddr *) &playerBlack_addr,
                         &len_blackPlayer);

            if (n == sizeof (msg)){
                print_msg_move_form_client(msg);
                move_result = board->makeMove(board,
                                              &msg.move_position.startPosition,
                                              &msg.move_position.endPosition,
                                              msg.direction,
                                              black);
                black_score = msg.score;

                display_game_info(board, white_score, black_score, game_state);
                msg_for_client = msg;
                msg_for_client.score = black_score;
                sendto(network_context->sock,
                       &msg_for_client,
                       sizeof (msg_for_client),
                       0,
                       (const struct sockaddr *) &playerWhite_addr,
                       len_whitePlayer);

                if(msg.isSurrender == true){
                    printf("Черные сдались! Конец игры!\n");
                    break;
                }
                if (black_score == 12){
                    printf("Конец игры!\n");
                    break;
                }
                print_msg_move_for_client(msg_for_client);
            } else {
                printf("Пакет не дошел\n");
            }
            if (msg.type == Default){
                game_state->switchPlayer(game_state);
            }
            else {
                continue;
            }
        }
    }
    network_fini(network_context);
    return 0;
}

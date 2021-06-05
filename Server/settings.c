#include "header.h"

void sign_in(NetworkContext *ctx, sockaddr_in *playerWhite_addr, sockaddr_in *playerBlack_addr){
    char buffer[MAXLINE];
    char *name_first = malloc(sizeof (char)*10);
    char *name_second = malloc(sizeof (char)*10);
    int n;
    sockaddr_in cliaddr;
    int len = sizeof (cliaddr);

    n = recvfrom(ctx->sock,
                 (char*)buffer,
                 MAXLINE,
                 MSG_WAITALL,
                 (struct sockaddr *)&cliaddr,
                 &len);
    if (n != 1){
        name_first = buffer;
        *playerWhite_addr = cliaddr;
        printf("Добавлен игрок %s", name_first);
        char buff[MAXLINE];
        *buff = *inet_ntop(AF_INET, &playerWhite_addr, buff, sizeof (buff));
        printf("adress 1: %s\n", buff);
    }


    n = recvfrom(ctx->sock,
                 (char*)buffer,
                 MAXLINE,
                 MSG_WAITALL,
                 (struct sockaddr *)&cliaddr,
                 &len);
    if(n != 1){
        name_second = buffer;
        *playerBlack_addr = cliaddr;
        printf("Добавлен игрок %s", name_second);
        char buff[MAXLINE];
        *buff = *inet_ntop(AF_INET, &playerBlack_addr, buff, sizeof (buff));
        printf("adress 2: %s\n", buff);
    }
}

void send_settings(NetworkContext *ctx, sockaddr_in playerWhite_addr, sockaddr_in playerBlack_addr){
    char ans[MAXLINE];

    ans[0] = '1';
    sendto(ctx->sock,
           (const char*) ans,
           strlen(ans),
           0,
           (const struct sockaddr *) &playerWhite_addr,
           sizeof (playerWhite_addr));

    ans[0] = '0';
    sendto(ctx->sock,
           (const char*) ans,
           strlen(ans),
           0,
           (const struct sockaddr *) &playerBlack_addr,
           sizeof (playerBlack_addr));


}

void print_msg_move_form_client(Message msg){
    printf("Ход получен: %d %d %d %d\n",
           msg.move_position.startPosition.x,
           msg.move_position.startPosition.y,
           msg.move_position.endPosition.x,
           msg.move_position.endPosition.y);
}

void print_msg_move_for_client(Message msg){
    printf("Ход отправлен: %d %d %d %d\n", msg.move_position.startPosition.x,
           msg.move_position.startPosition.y,
           msg.move_position.endPosition.x,
           msg.move_position.endPosition.y);
}

void display_game_info(Board *board, unsigned short white_score, unsigned short black_score, Game *gamestate){
    print_board(board);
    if (gamestate->currentPlayer == white){
        printf("Счет белых: %d\nСчет черных: %d\n", white_score, black_score);
    } else {
        printf("Счет черных: %d\nСчет белых: %d\n", black_score, white_score);
    }
}

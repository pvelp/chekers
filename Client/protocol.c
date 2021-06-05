#include "protocol.h"

NetworkContext *network_init(uint16_t port, in_addr_t server_addr)
{
    NetworkContext *ctx = malloc(sizeof(NetworkContext));

    if (!ctx) goto _error1;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("socket creation failed");
        goto _error2;
    }
    ctx->sock = sock;

    memset(&ctx->server_addr, 0, sizeof(ctx->server_addr));

    ctx->server_addr.sin_family = AF_INET;
    ctx->server_addr.sin_port = htons(port);
    ctx->server_addr.sin_addr.s_addr = htonl(server_addr);

    return ctx;

_error2:
    free(ctx);
_error1:
    return NULL;
}

int network_recv(const NetworkContext *network_context,
                 Message *msg,
                 size_t msg_size)
{
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    memcpy(&servaddr, &network_context->server_addr, sizeof(servaddr));

    ssize_t n = recvfrom(network_context->sock,
                         msg,
                         msg_size,
                         0,
                         (struct sockaddr *) &servaddr,
                         &len);

    return n;
}

int sendto_server_move(NetworkContext *network_context,
                       Message msg){
    ssize_t len = sendto(network_context->sock,
                         &msg,
                         sizeof (msg),
                         0,
                         (const struct sockaddr*)&network_context->server_addr,
                         sizeof (network_context->server_addr));
    return len;
}

int add_player(struct _NetworkContext* network_context
               ,char* name
               ,char* buffer
               ,Board *board){
    clear();
    printf("Введите ваше имя: ");
    fgets(name, MAXLINE - 1, stdin);
    name[MAXLINE - 1] = '\0';
    sendto(network_context->sock
           ,(char*) name
           ,MAXLINE
           ,0
           ,(const struct sockaddr *) &network_context->server_addr
           ,sizeof (network_context->server_addr));
    struct sockaddr_in cliaddr;
    unsigned int len = sizeof(cliaddr);
    int n = recvfrom(network_context->sock
                     ,(char*)buffer
                     ,MAXLINE
                     ,MSG_WAITALL
                     ,(struct sockaddr *) &network_context->server_addr
                     ,&len);
    buffer[n] = '\0';
    if (buffer[0] == '1'){
        clear();
        print_board(board);
        return 1;
    }else{
        clear();
        print_board(board);
        return 2;
    }
}


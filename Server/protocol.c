#include "header.h"

NetworkContext *network_init(uint16_t port)
{
    NetworkContext *ctx = malloc(sizeof(NetworkContext));
    if (!ctx) goto _error1;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("socket creation failed");
        goto _error2;
    }
    ctx->sock = sock;

    memset(&ctx->addr, 0, sizeof(ctx->addr));

    ctx->addr.sin_family = AF_INET;
    ctx->addr.sin_addr.s_addr = INADDR_ANY;
    ctx->addr.sin_port = htons(port);

    int bind_status = bind(ctx->sock,
                           (const struct sockaddr *) &ctx->addr,
                           sizeof(ctx->addr));
    if (bind_status < 0)
    {
        perror("bind failed");
        goto _error3;
    }

    return ctx;

_error3:
    close(ctx->sock);
_error2:
    free(ctx);
_error1:
    return NULL;
}

void network_fini(NetworkContext *ctx)
{
    if (ctx) {
        if (ctx->sock >= 0) close(ctx->sock);
        free(ctx);
    }
}

void get_from_client_move(NetworkContext *network_context, sockaddr_in clieaddr, const char *message,
                          struct MovePosition *move_position){
    int n;
    int len = sizeof (clieaddr);
    sendto(network_context->sock,
           (const char*)message,
           strlen(message),
           0,
           (const struct sockaddr *) &clieaddr,
           sizeof (clieaddr));
    printf("Отправлен запрос на ход!\n");
    n = recvfrom(network_context->sock,
                 &move_position,
                 sizeof(move_position),
                 MSG_WAITALL,
                 (struct sockaddr *) &clieaddr,
                 &len);
}

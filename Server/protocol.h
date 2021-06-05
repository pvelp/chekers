#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "header.h"

struct _NetworkContext {
    int sock;
    struct sockaddr_in addr;
};

typedef struct _NetworkContext NetworkContext;

typedef struct sockaddr_in sockaddr_in ;

NetworkContext *network_init(uint16_t port);
void network_fini(NetworkContext *ctx);

enum MessageType{
    EnterMoveMessage = 4,
    LastMove = 5,
    Default = -1,
    CombatAgain = 9
};

struct Message{
    enum MessageType type;
    struct MovePosition move_position;
    bool direction;
    bool isSurrender;
    unsigned short score;
};
typedef struct Message Message;

void get_from_client_move(NetworkContext *network_context, sockaddr_in clieaddr, const char *message,
                          struct MovePosition *move_position);

#endif // PROTOCOL_H

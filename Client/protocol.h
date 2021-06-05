#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "header.h"

struct _NetworkContext {
    int sock;
    struct sockaddr_in server_addr;
};

typedef struct _NetworkContext NetworkContext;

NetworkContext *network_init(uint16_t port, in_addr_t server_addr);

enum MessageType{
    EnterMoveMessage = 0,
    LastMove = 5,
    Default = -1,
    CombatAgain = 9,
    GameOver = 10
};

struct Message{
    enum MessageType type;
    struct MovePosition move_position;
    bool direction;
    bool isSurrender;
    unsigned short score;
};
typedef struct Message Message;

int network_recv(const NetworkContext *network_context,
                 Message *msg,
                 size_t msg_size);

int sendto_server_move(NetworkContext *network_context,
                       Message msg);

int add_player(struct _NetworkContext* network_context
               ,char* name
               ,char* buffer
               ,struct Board *board);

#endif

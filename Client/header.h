#ifndef HEADER_H
#define HEADER_H


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>


#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


#include "board.h"
#include "game.h"
#include "protocol.h"
#include "settings.h"


#define BLACK_CHECKER_BLACKCELL "\033[48;5;16;38;5;45m"
#define WHITE_CHECKER_BLACKCELL "\033[48;5;16;38;5;196m"
#define BLANK_BLACKCELL "\033[48;5;16m"
#define BLANK_WHITECELL "\033[48;5;255m"
#define COLOR_RESET "\033[0m"


#define PORT	8105
#define MAXLINE 1024


#define MOD "\x1b[5m"
#define STOP "\x1b[0m"

#endif

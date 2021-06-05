#ifndef HEADER_H
#define HEADER_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "board.h"
#include "game.h"
#include "protocol.h"
#include "Settings.h"

#define PORT	8105
#define MAXLINE 1024

#endif

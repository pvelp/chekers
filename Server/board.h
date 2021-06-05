#ifndef BOARD_H
#define BOARD_H
#include "header.h"

typedef struct Position
{
    int x;
    int y;
} Position;

struct MovePosition
{
    struct Position startPosition;
    struct Position endPosition;
};


enum State{BLACK, WHITE, BLANK};

typedef  struct Cell
{
    Position position;
    int color;
    bool isQueen;
    char (*CastColor)(struct Cell *self);
} Cell;
char CastColor(struct Cell *self);
Cell *newCell(int color, int x, int y);


enum MoveResult {SUCCESSFUL_MOVE, SUCCESSFUL_COMBAT, PROHIBITED};

typedef struct Board
{
    int boardSize;
    Cell cells[64];
    void (*del)(struct Board *self);
    void (*resetMap)(struct Board *self);
    enum MoveResult (*validMove)(struct Board *self, Position *startPos, Position *endPos, bool direction, int player);
    enum MoveResult (*makeMove)(struct Board *self, Position *startPos, Position *endPos, bool direction, int player);
} Board;

Board *newBoard();
void reset_map(Board *self);
int findCell(struct Board *self, Position *pos);
void delete_board(Board *self);
void print_board(Board *sefl);
enum MoveResult validMove (struct Board *self, Position *startPos, Position *endPos, bool direction, int player);
enum MoveResult makeMove (struct Board *self, Position *startPos, Position *endPos, bool direction, int player);

#endif // BOARD_H

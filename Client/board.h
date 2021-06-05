#ifndef BOARD_H
#define BOARD_H
#include "header.h"

typedef struct Position
{
    int x;
    int y;
} Position;

typedef  struct Cell
{
    Position position;
    int color;
    bool isQueen;
} Cell;

enum State{BLACK, WHITE, BLANK};

Cell *newCell(int color, int x, int y);
char CastColor(struct Cell *self);


struct MovePosition
{
    struct Position startPosition;
    struct Position endPosition;
};

struct MovePosition getMove ();
struct MovePosition *newMovePosition();

enum MoveResult {SUCCESSFUL_MOVE, SUCCESSFUL_COMBAT, PROHIBITED};

typedef struct Board
{
    int boardSize;
    Cell cells[64];
} Board;

Board *newBoard();
void delete_board(Board *self);
void reset_map(Board *self);
int findCell(struct Board *self, Position *pos);
enum MoveResult validMove (struct Board *self, Position *startPos, Position *endPos, bool direction, int player);
enum MoveResult makeMove (struct Board *self, Position *startPos, Position *endPos, bool direction, int player);
void print_board(Board *sefl);

void clear();

#endif // BOARD_H

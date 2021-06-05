#include "header.h"

Cell *newCell(int color, int x, int y)
{
    Cell *cell;

    if(!(cell = (Cell *)malloc(sizeof (Cell)))){
        return NULL;
    }
    cell->color=color;
    cell->position.x = x;
    cell->position.y = y;
    cell->isQueen = false;
    return cell;
    free(cell);
}

char CastColor(struct Cell *self){
    char result;
    switch (self->color) {
    case BLACK:
        if (self->isQueen){
            result = 'B';
        } else {
            result = 'b';
        }
        break;
    case WHITE:
        if (self->isQueen){
            result = 'W';
        } else {
            result = 'w';
        }
        break;
    case BLANK:
        result = ' ';
        break;
    }
    return result;
}

Board *newBoard(){
    Board *board;
    if(!(board = (Board*)malloc(sizeof (Board)))){
        free(board);
        return NULL;
    }

    Cell *cells;
    if(!(cells = (Cell*)malloc(sizeof (Cell)))){
        free(cells);
        return NULL;
    }

    for (size_t i = 0; i < 64; ++i){
        board->cells[i] = *cells;
    }
    board->boardSize = 8;

    return board;
    free(cells);
    free(board);
}

void delete_board(Board *self){
    free(self->cells);
    free(self);
}

void reset_map(Board *self){
    Cell *cell;
    cell = newCell(BLANK, -1, -1);
    int k = 0;
    int boardSize = 8;
    for (int j = 0; j < boardSize; ++j){
        for (int i = 0; i < boardSize; ++i){
            if(j == 0 && i % 2 != 0){
                cell->color = WHITE;
                cell->isQueen = false;
            } else if(j == 1 && i % 2 == 0){
                cell->color = WHITE;
                cell->isQueen = false;
            } else if(j == 2 && i % 2 != 0){
                cell->color = WHITE;
                cell->isQueen = false;
            } else if (j == 5 && i % 2 == 0){
                cell->color = BLACK;
                cell->isQueen = false;
            } else if (j == 6 && i % 2 != 0){
                cell->color = BLACK;
                cell->isQueen = false;
            } else if (j == 7 && i % 2 == 0){
                cell->color = BLACK;
                cell->isQueen = false;
            } else {
                cell->color = BLANK;
                cell->isQueen = false;
            }
            cell->position.x = i;
            cell->position.y = j;
            self->cells[k] = *cell;
            k++;
        }
    }
    free(cell);
}

int findCell(struct Board *self, Position *pos){
    int res;
    for (int i = 0; i < 64; ++i){
        if (self->cells[i].position.x == pos->x && self->cells[i].position.y == pos->y){
            res = i;
            break;
        }
    }
    return res;
}

enum MoveResult validMove(struct Board *self, Position *startPos, Position *endPos, bool direction, int player){
    enum MoveResult res = PROHIBITED;
    int dx = startPos->x - endPos->x;
    int dy = startPos->y - endPos->y;

    if (endPos->x >= 0 && endPos->x < self->boardSize && endPos->y >= 0 && endPos->y < self->boardSize){
        if (!self->cells[findCell(self, startPos)].isQueen){
            int targetCell = findCell(self, endPos); //ищем клетку с данными координатами
            if (self->cells[targetCell].color == BLANK){ //если не заполнена, то можем ходить
                Position *enemyPosition = malloc(sizeof (int) * 2);
                if(!enemyPosition){
                    return -1;
                }//возможные координаты пешки соперника
                enemyPosition->x = (startPos->x + endPos->x) / 2;
                enemyPosition->y = (startPos->y + endPos->y) / 2;
                int enemyCell = findCell(self, enemyPosition); //находим на доске эту позицию
                int startCell = findCell(self, startPos);
                if(abs(dx) == 2 && abs(dy) == 2){ //если едим;
                    res = self->cells[targetCell].color != self->cells[enemyCell].color
                            && self->cells[startCell].color != self->cells[enemyCell].color
                            ? SUCCESSFUL_COMBAT : res; //если на клетке на которую идем не стоит пешка соперни и не стоит пешка нашего цвето, то саксес иначе прохиб
                } else if ((abs(dx) == 1 && dy == 1 && direction) || (abs(dx) == 1 && dy == -1 && !direction)){
                    res = SUCCESSFUL_MOVE;
                }
                free(enemyPosition);
            }

        } else {
            int our_color = self->cells[findCell(self, startPos)].color;
            if (our_color == self->cells[findCell(self, endPos)].color){
                res = PROHIBITED;
            } else {
            if (endPos->x < startPos->x && endPos->y < startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                int k = 0;
                int n = 0;
                for (int i = 1; i < abs(dx); ++i){
                    pos->x = endPos->x + i;
                    pos->y = endPos->y + i;
                    int tmp_pos_color = self->cells[findCell(self, pos)].color;
                    if (tmp_pos_color != BLANK && tmp_pos_color == our_color){
                        k++;
                    }
                    if (tmp_pos_color != BLANK && tmp_pos_color != our_color){
                        n++;
                    }
                }
                if (k == 0 && n == 0){
                    res = SUCCESSFUL_MOVE;
                } else if (n == 1 && k == 0){
                    res = SUCCESSFUL_COMBAT;
                } else {
                    res = PROHIBITED;
                }
                free(pos);
            } else if (endPos->x < startPos->x && endPos->y > startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    exit(1);
                }
                int k = 0;
                int n = 0;
                for (int i = 1; i < abs(dx); ++i){
                    pos->x = endPos->x + i;
                    pos->y = endPos->y - i;
                    int tmp_pos_color = self->cells[findCell(self, pos)].color;
                    if (tmp_pos_color != BLANK && tmp_pos_color == our_color){
                        k++;
                    }
                    if (tmp_pos_color != BLANK && tmp_pos_color != our_color){
                        n++;
                    }
                }

                if (k == 0 && n == 0){
                    res = SUCCESSFUL_MOVE;
                } else if (n == 1 && k == 0){
                    res = SUCCESSFUL_COMBAT;
                } else {
                    res = PROHIBITED;
                }
                free(pos);
            } else if (endPos->x > startPos->x && endPos->y < startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                int k = 0;
                int n = 0;
                for (int i = 1; i < abs(dx); ++i){
                    pos->x = endPos->x - i;
                    pos->y = endPos->y + i;
                    int tmp_pos_color = self->cells[findCell(self, pos)].color;
                    if (tmp_pos_color != BLANK && tmp_pos_color == our_color){
                        k++;
                    }
                    if (tmp_pos_color != BLANK && tmp_pos_color != our_color){
                        n++;
                    }
                }
                if (k == 0 && n == 0){
                    res = SUCCESSFUL_MOVE;
                } else if (n == 1 && k == 0){
                    res = SUCCESSFUL_COMBAT;
                } else {
                    res = PROHIBITED;
                }
                free(pos);
            } else if (endPos->x > startPos->x && endPos->y > startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                int k = 0;
                int n = 0;
                for (int i = 1; i < abs(dx); ++i){
                    pos->x = endPos->x - i;
                    pos->y = endPos->y - i;
                    int tmp_pos_color = self->cells[findCell(self, pos)].color;
                    if (tmp_pos_color != BLANK && tmp_pos_color == our_color){
                        k++;
                    }
                    if (tmp_pos_color != BLANK && tmp_pos_color != our_color){
                        n++;
                    }
                }
                if (k == 0 && n == 0){
                    res = SUCCESSFUL_MOVE;
                } else if (n == 1 && k == 0){
                    res = SUCCESSFUL_COMBAT;
                } else {
                    res = PROHIBITED;
                }
                free(pos);
                if (dx != dy){
                    res = PROHIBITED;
                }
            }
        }
    }
    }
    if (player == white){
        if (self->cells[findCell(self, startPos)].color != WHITE){
            res = PROHIBITED;
        }
    } else {
        if (self->cells[findCell(self, startPos)].color != BLACK){
            res = PROHIBITED;
        }
    }
    return res;
}

enum MoveResult makeMove(struct Board *self, Position *startPos, Position *endPos, bool direction, int player){
    enum MoveResult moveResult = validMove(self, startPos, endPos, direction, player);
    switch (moveResult) {
    case SUCCESSFUL_MOVE:

        if (endPos->y == 7 && self->cells[findCell(self, startPos)].color == WHITE && !self->cells[findCell(self, startPos)].isQueen){
            self->cells[findCell(self, startPos)].isQueen = true;
        }
        if (endPos->y == 0 &&  self->cells[findCell(self, startPos)].color == BLACK && !self->cells[findCell(self, startPos)].isQueen){
            self->cells[findCell(self, startPos)].isQueen = true;
        }

        self->cells[findCell(self, endPos)].color = self->cells[findCell(self, startPos)].color;
        self->cells[findCell(self, endPos)].isQueen = self->cells[findCell(self, startPos)].isQueen;
        self->cells[findCell(self, startPos)].color = BLANK;
        self->cells[findCell(self, startPos)].isQueen = false;
        break;
    case SUCCESSFUL_COMBAT:
        if (!self->cells[findCell(self, startPos)].isQueen){
            if (endPos->y == 7 && self->cells[findCell(self, startPos)].color == WHITE){
                self->cells[findCell(self, startPos)].isQueen = true;
            }
            if (endPos->y == 0 &&  self->cells[findCell(self, startPos)].color == BLACK){
                self->cells[findCell(self, startPos)].isQueen = true;
            }

            self->cells[findCell(self, endPos)].color = self->cells[findCell(self, startPos)].color;
            self->cells[findCell(self, endPos)].isQueen = self->cells[findCell(self, startPos)].isQueen;
            self->cells[findCell(self, startPos)].color = BLANK;
            self->cells[findCell(self, startPos)].isQueen = false;

            Position *enemyPosition = malloc(sizeof (int) * 2);
            if(!enemyPosition){
                return -1;
            }
            enemyPosition->x = (startPos->x + endPos->x) / 2;
            enemyPosition->y = (startPos->y + endPos->y) / 2;
            self->cells[findCell(self, enemyPosition)].color = BLANK;
            break;

        } else {

            self->cells[findCell(self, endPos)].color = self->cells[findCell(self, startPos)].color;
            self->cells[findCell(self, endPos)].isQueen = self->cells[findCell(self, startPos)].isQueen;
            self->cells[findCell(self, startPos)].color = BLANK;
            self->cells[findCell(self, startPos)].isQueen = false;

            int tmp_pos_color;
            int current_color;

            if(endPos->x < startPos->x && endPos->y < startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                for (int i = 1; i < abs(endPos->x-startPos->x); ++i){
                    pos->x = endPos->x + i;
                    pos->y = endPos->y + i;
                    tmp_pos_color = self->cells[findCell(self, pos)].color;
                    current_color = self->cells[findCell(self, startPos)].color;
                    if (current_color != tmp_pos_color && tmp_pos_color != BLANK){
                        self->cells[findCell(self, pos)].color = BLANK;
                        self->cells[findCell(self, pos)].isQueen = false;
                        break;
                    }
                }
            }

            if(endPos->x > startPos->x && endPos->y < startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                for (int i = 1; i < abs(endPos->x-startPos->x); ++i){
                    pos->x = endPos->x - i;
                    pos->y = endPos->y + i;
                    tmp_pos_color = self->cells[findCell(self, pos)].color;
                    current_color = self->cells[findCell(self, startPos)].color;
                    if (current_color != tmp_pos_color && tmp_pos_color != BLANK){
                        self->cells[findCell(self, pos)].color = BLANK;
                        self->cells[findCell(self, pos)].isQueen = false;
                        break;
                    }
                }
            }
            if(endPos->x < startPos->x && endPos->y > startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                for (int i = 1; i < abs(endPos->x-startPos->x); ++i){
                    pos->x = endPos->x + i;
                    pos->y = endPos->y - i;
                    tmp_pos_color = self->cells[findCell(self, pos)].color;
                    current_color = self->cells[findCell(self, startPos)].color;
                    if (current_color != tmp_pos_color && tmp_pos_color != BLANK){
                        self->cells[findCell(self, pos)].color = BLANK;
                        self->cells[findCell(self, pos)].isQueen = false;
                        break;
                    }
                }
            }
            if(endPos->x > startPos->x && endPos->y > startPos->y){
                Position *pos = malloc(sizeof (int) * 2);
                if (!pos){
                    return -1;
                }
                for (int i = 1; i < abs(endPos->x-startPos->x); ++i){
                    pos->x = endPos->x - i;
                    pos->y = endPos->y - i;
                    tmp_pos_color = self->cells[findCell(self, pos)].color;
                    current_color = self->cells[findCell(self, startPos)].color;
                    if (current_color != tmp_pos_color && tmp_pos_color != BLANK){
                        self->cells[findCell(self, pos)].color = BLANK;
                        self->cells[findCell(self, pos)].isQueen = false;
                        break;
                    }
                }
            }
        }
    }
    return moveResult;
}

void print_board(Board *self){
    int k = 0;
    int s = self->boardSize;
    printf("  ");
    for (int i = 0; i < 8; ++i){
        printf(" %d ", i);
    }
    for (int j = 0; j < 8; ++j){
        printf("\n%d ", j);
        for (int i = k; i < s; ++i){
            Cell *currentCell = (Cell*)malloc(sizeof (Cell));
            if (!currentCell){
                exit(1);
            }
            *currentCell = self->cells[i];
            switch (currentCell->color) {
            case 0:
                printf(BLACK_CHECKER_BLACKCELL " %c " COLOR_RESET, CastColor(currentCell));
                break;
            case 1:
                printf(WHITE_CHECKER_BLACKCELL " %c " COLOR_RESET, CastColor(currentCell));
                break;
            case 2:
                if (j % 2 == 0){
                    if (i % 2 == 0){
                        printf(BLANK_WHITECELL " %c " COLOR_RESET, CastColor(currentCell));
                    } else {
                        printf(BLANK_BLACKCELL " %c " COLOR_RESET, CastColor(currentCell));
                    }
                } else {
                    if (i % 2 == 0){
                        printf(BLANK_BLACKCELL " %c " COLOR_RESET, CastColor(currentCell));
                    } else {
                        printf(BLANK_WHITECELL " %c " COLOR_RESET, CastColor(currentCell));
                    }
                }
            }
            free(currentCell);
        }
        k += 8;
        s += 8;
    }
    printf("\n ");
    printf("\n");
}

struct MovePosition *newMovePosition(){
    struct MovePosition *mp = malloc(sizeof (struct MovePosition));
    if (!mp){
        return NULL;
    }

    mp->startPosition.x = 0;
    mp->startPosition.y = 0;
    mp->endPosition.x = 1;
    mp->endPosition.y = 1;
    return mp;
}

struct MovePosition getMove (){
    struct MovePosition mp;
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    while (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7){
        printf("Введите валидный ход (введите 0 0 0 0, если хотите сдаться): ");
        scanf("%d%d %d%d", &x1, &y1, &x2, &y2); //вводим двузначное число, первая цифра числа коориданат х, вторая у
    }
    mp.startPosition.x = x1;
    mp.startPosition.y = y1;
    mp.endPosition.x = x2;
    mp.endPosition.y = y2;
    return mp;
}

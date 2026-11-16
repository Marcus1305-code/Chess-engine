#include <stdio.h>
#include <stdlib.h>


enum piece {empty, pawn, knight, bishop, rook, queen, king};
enum piece_color {white, black, none};
enum direction {NORTH,SOUTH, EAST, WEST, NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST};
struct piece_in_chess {
    enum piece piece;
    enum piece_color piece_color;
    enum direction direction;
    int movement_pattern;
    int moved;
};
struct board {
    int size;
    struct piece_in_chess *piece_in_chess;
};
void print_board(struct board *board);
void chess_board(struct board *board);
struct piece_in_chess get_cell(struct board board, int x, int y);
void insert_board(struct board *board, int x, int y,enum piece pieces, enum piece_color color);
void initialize_board(struct board *board);

int main(void) {
    struct board b;
    b.size = 8;
    chess_board(&b);
    initialize_board(&b);
    print_board(&b);
    free(b.piece_in_chess);
    return 0;
}

unsigned int piece_moves(enum piece piece, enum piece_color color) {
    unsigned int north      = 1u << NORTH;
    unsigned int south      = 1u << SOUTH;
    unsigned int east       = 1u << EAST;
    unsigned int west       = 1u << WEST;
    unsigned int north_east = 1u << NORTH_EAST;
    unsigned int north_west = 1u << NORTH_WEST;
    unsigned int south_east = 1u << SOUTH_EAST;
    unsigned int south_west = 1u << SOUTH_WEST;
    //0 = pawn 1=knight 2=bishop 3=rook 4=queen 5=king
    switch (piece) {
        case 1: //pawn
            if (color == white) {
                return north | north_east | north_west;
            } else {
                return south | south_east | south_west;
            }
            break;
        case 2: //knight
            if (color == white) {
                return north | south | east | west;
            } else {
                return north | south | east | west;
            }
            break;
        case 3: //bishop
            if (color == white) {
                return north_east | north_west | south_east | south_west;
            } else {
                return north_east | north_west | south_east | south_west;
            }
            break;
        case 4: //rook
            if (color == white) {
                return north | south | east | west;
            } else {
                return north | south | east | west;
            }
            break;
        case 5: //queen
            if (color == white) {
                return north |north_east| north_west | south | south_east| south_west | east | west;
            } else {
                return north |north_east| north_west | south | south_east| south_west | east | west;
            }
            break;
        case 6: // king
            if (color == white) {
                return north |north_east| north_west | south | south_east| south_west | east | west;
            } else {
                return north |north_east| north_west | south | south_east| south_west | east | west;
            }
            break;
        default:
            break;
    }
    return 0;
}

void chess_board(struct board *board) {
    int index = 0;
    int size = board->size;
    board->piece_in_chess = malloc(sizeof(struct piece_in_chess) * size * size);
    if (board->piece_in_chess == NULL) {
        return;
    }
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            index = x * size + y;
            board->piece_in_chess[index].piece = empty;
        }
    }
}

struct piece_in_chess get_cell(struct board board, int x, int y) {
    int size = board.size;
    return board.piece_in_chess[x * size + y];
}

void insert_board(struct board *board, int x, int y,enum piece pieces, enum piece_color color) {
    int index;
    int size = board->size;
    index = x * size + y;
    board->piece_in_chess[index].piece = pieces;
    board->piece_in_chess[index].piece_color = color;
}

void initialize_board(struct board *board) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if ((x == 0 && y == 0) ||(x == 7 && y == 0)) {
                insert_board(board, x, y, rook, white);
            }
            if ((x == 1 && y == 0) || (x == 6 && y == 0)) {
                insert_board(board, x, y, knight, white);
            }
            if ((x == 2 && y == 0) || (x == 5 && y == 0)) {
                insert_board(board, x, y, bishop, white);
            }
            if (x == 3 && y == 0) {
                insert_board(board, x, y, queen, white);
            }
            if (x == 4 && y == 0) {
                insert_board(board, x, y, king, white);
            }
            if (y == 1) {
                insert_board(board, x, y, pawn, white);
            }
            //--------------------------------------- sort
            if ((x == 0 && y == 7) || (x == 7 && y == 7)) {
                insert_board(board, x, y, rook, black);
            }
            if ((x == 1 && y == 7) || (x == 6 && y == 7)) {
                insert_board(board, x, y, knight, black);
            }
            if ((x == 2 && y == 7) || (x == 5 && y == 7)) {
                insert_board(board, x, y, bishop, black);
            }
            if (x == 3 && y == 7) {
                insert_board(board, x, y, queen, black);
            }
            if (x == 4 && y == 7) {
                insert_board(board, x, y, king, black);
            }

            if (y == 6) {
                insert_board(board, x, y, pawn, black);
            }
            if (y == 5 || y == 4 || y == 3 || y == 2) {
                insert_board(board, x, y, empty, none);
            }
        }
    }
}

void print_board(struct board *board) {
    int index;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            struct piece_in_chess pieces = get_cell(*board, x, y);
            printf(" %d",pieces.piece);
            printf(" %d", pieces.piece_color);
        }
        printf("\n");
    }
}

//laver på skolen med whiteboard for at forstå koden her. der skal også convertes
//fra tal til chars og symbol ændring for at få et nice print
void pawn_movement(struct board *board) {

}
void knight_movement(struct board *board, int x, int y) {

}
void bishop_movement(struct board *board) {

}
void rook_movement(struct board *board, int x, int y, int turn, int new_x, int new_y) {
    struct piece_in_chess rk = get_cell(*board, x, y);
    struct piece_in_chess rk_new = get_cell(*board, new_x, new_y);
    //starten af passage af andre brikker af ens egne
    //her tjekkes for farve mellem alle pladserne
    for (int i = 0; i < 8; i++) {

    }
    if (1/**/) {

        return;
    }
    unsigned int movement_pattern = piece_moves(rook, turn);
    if (1) {

    }
    //
}
void queen_movement(struct board *board) {

}
void king_movement(struct board *board) {

}
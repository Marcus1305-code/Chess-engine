#include <stdio.h>
#include <stdlib.h>

int not_moved();
int emeny_pawn();
enum piece {pawn, knight, bishop, rook, queen, king};
enum piece_color {white, black};
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

int main(void) {
    printf("Hello, World!\n");
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
        case 0: //pawn
            if (color == white) {
                return north | north_east | north_west;
            } else {
                return south | south_east | south_west;
            }
            break;
        case 1: //knight
            if (color == white) {
                return north | south | east | west;
            } else {
                return north | south | east | west;
            }
            break;
        case 2: //bishop
            if (color == white) {
                return north_east | north_west | south_east | south_west;
            } else {
                return north_east | north_west | south_east | south_west;
            }
            break;
        case 3: //rook
            if (color == white) {
                return north | south | east | west;
            } else {
                return north | south | east | west;
            }
            break;
        case 4: //queen
            if (color == white) {
                return north |north_east| north_west | south | south_east| south_west | east | west;
            } else {
                return north |north_east| north_west | south | south_east| south_west | east | west;
            }
            break;
        case 5: // king
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

int possible_moves() {
    switch () {
        case 0:
            break;
        case 1:
            break;
    }
    return 0;
}
void chess_board() {
    int index = 0;
    int size = 8;
    int *board = malloc(sizeof(int) * size * size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            board[x * size + y] = -1;
        }
    }
}
struct piece_in_chess get_cell(struct board board, int x, int y) {
    int size = board.size;
    return board.piece_in_chess[x * size + y];
}
/*
 *initialize_board(): Opsæt hele skakbrættet med alle 32 brikker ved at bruge insert_board().
 *insert_board(): Placér én brik på en bestemt position med en bestemt farve.
 */
// er en start men ikke færdig skal laves nogle ændringer i
struct board insert_board(struct board board, int x, int y, enum piece pieces, enum piece_color color) {
    int size = board.size;
    board.piece_in_chess->piece_color = white;
    for (int i = 0; i < 8; i++) {
        board.piece_in_chess[1 * size + i].piece_color = white;
        board.piece_in_chess[1 * size + i].piece = pawn;
    }
    return board;
}
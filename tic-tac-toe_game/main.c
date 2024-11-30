#include <stdbool.h>
#include <stdio.h>

typedef struct Player {
    char sign;
    unsigned int score;
} plr;

void init_board(char board[3][3]);
void print_board(const char board[3][3]);
int evaluate_board(const char board[3][3]);
int print_scores(const plr* p1, const plr* p2);

int main(void) {
    char board[3][3];
    plr p1 = {'X', 0}, p2 = {'O', 0};
    init_board(board);
    while (true) {
        plr* turn = &p1;
        print_scores(&p1, &p2);
        print_board(board);
        
    }
}

// initializing board
void init_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// fast aur jyada redable algorithm
void print_board(const char board[3][3]) {
    printf("%c", '\n');
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("%c", '\n');
}

// board ke current condition pe score dena
int evaluate_board(const char board[3][3]) {
    // rows && col
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            if (board[i][0] == 'X') return 10;
            if (board[i][0] == 'O') return -10;
        }
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            if (board[0][i] == 'X') return 10;
            if (board[0][i] == 'O') return -10;
        }
    }
    // dig 1
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        if (board[0][0] == 'X') return 10;
        if (board[0][0] == 'O') return -10;
    }
    // dig 2
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        if (board[0][2] == 'X') return 10;
        if (board[0][2] == 'O') return -10;
    }
    // no match
    return 0;
}

int print_scores(const plr* p1, const plr* p2) {
    printf("> Scores:-\n");
    printf("  Player %c: %d\n", p1->sign, p1->score);
    printf("  Player %c: %d\n", p2->sign, p2->score);
}
#include <limits.h>
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
void player_move(const plr* p1, char board[3][3]);
void computer_move(const plr* p2, char board[3][3]);
int min_max(char board[3][3], int depth, char turn);
bool is_space_left(const char board[3][3]);

int main(void) {
    char board[3][3];
    // p1 is player and p2 is computer
    plr p1, p2;
    p1.score = 0;
    p2.score = 0;
    printf("Enter your sign(X, O): ");
    if (getchar() == 'X') {
        p1.sign = 'X';
        p2.sign = 'O';
    } else {
        p1.sign = 'O';
        p2.sign = 'X';
    }
    char turn = p1.sign;
    init_board(board);
    while (true) {
        print_scores(&p1, &p2);
        print_board(board);
        int eval = evaluate_board(board);
        if (eval == 10) {
            if (p1.sign == 'X') {
                printf("Player won!\n");
            } else {
                printf("Computer won!\n");
            }
        } else if (eval == -10) {
            if (p1.sign == 'O') {
                printf("Player won!\n");
            } else {
                printf("Computer won!\n");
            }
        } else if (!is_space_left) {
            printf("Draw match!\n");
            break;
        }
        if (turn == p1.sign) {
            player_move(&p1, board);
        } else {
            computer_move(&p2, board);
        }
        if (turn == 'X') {
            turn = 'O';
        } else {
            turn = 'X';
        }
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

void player_move(const plr* p1, char board[3][3]) {
    int row, col;
    printf("Enter row, col(%c): ", p1->sign);
    scanf("%d %d", &row, &col);
    board[row - 1][col - 1] = p1->sign;
}

bool is_space_left(const char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

int min_max(char board[3][3], int depth, char turn) {
    if (!is_space_left(board)) {
        return 0;
    }
    int eval = evaluate_board(board);
    if (eval == 10) {
        return eval - depth;
    }
    if (eval == -10) {
        return eval + depth;
    }
    int scores = (turn == 'X') ? INT_MIN : INT_MAX;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = turn;
                if (turn == 'X') {
                    int curr_scores = min_max(board, depth + 1, 'O');
                    scores = (curr_scores > scores) ? curr_scores : scores;
                    board[i][j] = ' ';
                } else {
                    int curr_scores = min_max(board, depth + 1, 'X');
                    scores = (curr_scores < scores) ? curr_scores : scores;
                    board[i][j] = ' ';
                }
            }
        }
    }
    return scores;
}

void computer_move(const plr* p2, char board[3][3]) {
    int row, col, scores = (p2->sign == 'X') ? INT_MIN : INT_MAX;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = p2->sign;
                if (p2->sign == 'X') {
                    int curr_scores = min_max(board, 0, 'O');
                    if (curr_scores > scores) {
                        scores = curr_scores;
                        row = i, col = j;
                    }
                } else {
                    int curr_scores = min_max(board, 0, 'X');
                    if (curr_scores < scores) {
                        scores = curr_scores;
                        row = i, col = j;
                    }
                }
                board[i][j] = ' ';
            }
        }
    }
    board[row][col] = p2->sign;
}
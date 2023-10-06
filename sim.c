// Team members:SHAURY PATEL(22110241),MUKUL MEENA(22110159),KAILA UDAY(22110111)
#include <stdio.h>
#include <assert.h>

enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

void init_board(board_t board)
{
    for (int line = 0; line < 15; ++line) {
        board[line] = NO;
    }
}

player_t other_player(player_t player)
{
    switch (player) {
    case RED: return BLUE;
    case BLUE: return RED;
    default: assert(0);
    }
}

int has_won(board_t board, player_t player)
{   
    player_t otherplayer=other_player(player);
    int triplets[20][3] = {
        {0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {0, 4, 8}, {1, 2, 9},
        {1, 3, 10}, {1, 4, 11}, {2, 3, 12}, {2, 4, 13}, {3, 4, 14},
        {5, 6, 9}, {5, 7, 10}, {5, 8, 11}, {6, 7, 12},
        {6, 8, 13}, {7, 8, 14}, {9, 10, 12}, {9, 11, 13}, {10, 11, 14}, {12, 13, 14}
    };

    for (int i = 0; i < 20; i++) {
        int a = triplets[i][0];
        int b = triplets[i][1];
        int c = triplets[i][2];
        if (board[a] == otherplayer && board[b] == otherplayer && board[c] == otherplayer) {
            return 1;
        }
    }

   return 0;
}


int is_full(board_t board)
{
    for (int line = 0; line < 15; ++line) {
        if (board[line] == NO){
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int line;
    /* -1 for a loss, 0 for a draw, 1 for a win. */
    int score;
} move_t;

/*
 * board should be an unfinished game.
 */
move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    for (int line = 0; line < 15; ++line) {
        if (board[line] == NO) {
            board[line] = player;
            if (has_won(board, player)) {
                board[line] = NO;
                return (move_t) {
                    line,
                    1
                };
            }
            board[line] = NO;
        }
    }

    for (int line = 0; line < 15; ++line) {
        if (board[line] == NO) {
            board[line] = player;

            response = best_move(board, other_player(player));
            board[line] = NO;

            if (is_full(board)) {
                return (move_t) {
                    .line = line,
                    .score = 0
                };
            }
            if (response.score == -1) {
                return (move_t) {
                    .line = line,
                    .score = 1
                };
            } else if (response.score == 0) {
                candidate = (move_t) {
                    .line = line,
                    .score = 0
                };
                no_candidate = 0;
            } else { /* response.score == +1 */
                if (no_candidate) {
                    candidate = (move_t) {
                        .line = line,
                        .score = -1
                    };
                    no_candidate = 0;
                }
            }
        }
    }
    return candidate;
}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        case NO: printf(".  "); break;
        }
    }
    printf("\n");
}

int main()
{
    int move, i;
    board_t board;
    move_t response;
    int player_choice;
    printf("First player or second player (1 or 2): ");
    scanf("%d", &player_choice);
    player_t current;

    if (player_choice == 1) {
        current = RED;
    } else if (player_choice == 2) {
        current = BLUE;
    } else {
        printf("\nInvalid choice");
        return 1; // Exit the program due to an invalid choice
    }

    init_board(board);

    while (1) {
        print_board(board);
        printf("\n\n");

        if (current == RED) {
            printf("0  1  2  3  4  5  6  7  8  9 10 11 12 13 14\n");
            printf("\nEnter your move: ");
            scanf("%d", &move);
            i = move;
            if (i >= 0 && i < 15 && board[i] == NO) {
                board[i] = current;
            } 
            else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            response = best_move(board, current);
            board[response.line] = current;
        }

        if (has_won(board, current)) {
            print_board(board);
            printf("Player %c has won!\n", (current == RED) ? 'R' : 'B');
            break;
        } else if (is_full(board)) {
            print_board(board);
            printf("It's a draw!\n");
            break;
        }

        current = other_player(current);
    }

    return 0;
}

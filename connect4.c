/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
#include <stdio.h>
#include <assert.h>

#define n 4
// Team members:SHAURY PATEL(22110241),MUKUL MEENA(22110159),KAILA UDAY(22110111)
typedef char player_t; 
typedef char board_t[4][5]; 

void init_board(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            board[row][col] = '.';
        }
    }
}


int is_full(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (board[row][col] == '.') { return 0; }
        }
    }
    return 1;
}

int has_won(board_t board, player_t player)
{
    int cont=0;
    for (int i=0;i<4;i++){
        cont=0;
        for (int j=0;j<4;j++){
            if (board[i][j]==player){
                cont++;
            }
        }
        if (cont==n){
            return 1;
        }
        cont=0;
        for (int j=1;j<5;j++){
            if (board[i][j]==player){
                cont++;
            }
        }
        if (cont==n){
            return 1;
        }
    }
    for (int j=0;j<5;j++){
        cont=0;
        for (int i=0;i<4;i++){
            if (board[i][j]==player){
                cont++;
            }
        }
        if (cont==n){
            return 1;
        }
    }
    cont=0;
    for (int i=0;i<4;i++){
        if (board[i][i]==player){
            cont++;
        }
    }
    if (cont==n){
        return 1;
    }
    cont=0;
    for (int i=0;i<4;i++){
        if (board[i][i+1]==player){
            cont++;
        }
    }
    if (cont==n){
        return 1;
    }
    cont=0;
    for (int i=0;i<4;i++){
        if (board[i][n-i]==player){
            cont++;
        }
    }
    if (cont==n){
        return 1;
    }
    cont=0;
    for (int i=0;i<4;i++){
        if (board[i][n-i-1]==player){
            cont++;
        }
    }
    if (cont==n){
        return 1;
    }
    return 0;
}

player_t other_player(player_t player)
{
    switch (player) {
    case 'r': return 'b';
    case 'b': return 'r';
    default: assert(0);
    }
}

typedef struct {
    int col;
    int score;
} move_t;

void add_element(board_t board,player_t player, int j){
    int i1=0;
    for (int i=0;i<4;i++){
        if (board[i][j]=='.'){
            i1=i;
        }
    }
    board[i1][j]=player;
}

void remove_element(board_t board, int j){
    int i1=0;
    for (int i=0;i<4;i++){
        if (board[i][j]!='.'){
            i1=i;
            break;
        }
    }
    board[i1][j]='.';
}
/*
 * board should be an unfinished game.
 */
move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));

    
        for (int col = 0; col < 5; ++col) {
            if (board[0][col] == '.') {
                add_element(board,player,col);
                if (has_won(board, player)) {
                    remove_element(board,col);
                    return (move_t) {
                        col,1
                    };
                }
                remove_element(board,col);
            }
        }

    
        for (int col = 0; col < 5; ++col) {
            
            if (board[0][col] == '.') {
                add_element(board,player,col);
                if (is_full(board)) {
                    remove_element(board,col);
                    return (move_t) {
                        col,0
                    };
                }

                response = best_move(board, other_player(player));
                remove_element(board,col);
                if (response.score == -1) {
                    return (move_t) {
                        .col=col,
                        .score=1
                    };
                } else if (response.score == 0) {
                    candidate = (move_t) {
                        .col = col,
                        .score = 0
                    };
                    no_candidate = 0;
                } else { /* response.score == +1 */
                    if (no_candidate) {
                        candidate = (move_t) {
                            .col = col,
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
    for(int i=0;i<4;i++){
        for (int j=0;j<5;j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n----------------------------------\n");
}


int main()
{
    board_t game;
    init_board(game);
    player_t player;
    player_t AI;
    player_t current;
    int temp;
    int column;
    printf("Choose red or blue\n");
    printf("Enter r for Red\n");
    printf("Enter b for Blue\n");
    scanf("%s",&temp);
    if (temp==1){
        player='r';
        AI='b';
    }
    else{
        player='b';
        AI='r';
    }
    printf("For playing \n");
    printf("For user enter 1\n");
    printf("For computer enter 2\n");
    scanf("%d",&temp);
    if (temp==1){
        current=player;
    }
    else{
        current=AI;
    }
    if (current==player){
    printf("Your turn (enter column 0-4): ");
    scanf("%d", &column);
    add_element(game, player, column);
    if (column==0){
        add_element(game,AI,1);
    }
    if (column==1){
        add_element(game,AI,4);
    }
    if (column==2){
        add_element(game,AI,4);
  }
    if (column==3){
        add_element(game,AI,0);
    }
    if (column==4){
        add_element(game,AI,3);
    }
    }
    else{
        add_element(game,AI,3);
        current=player;
    }
    
    while (1)
    {
        print_board(game);
        if (player == current)
        {
            printf("Your turn (enter column 0-4): ");
            scanf("%d", &column);
            if (column < 0 || column > 4 || game[0][column] != '.')
            {
                printf("Invalid move. Try again.\n");
                continue;
            }
            add_element(game, player, column);
            if (has_won(game, player))
            {
                print_board(game);
                printf("You win! Congratulations!\n");
                break;
            }
        }
        else
        {
            // Computer's turn
            move_t computerMove = best_move(game, current);
            printf("Computer's turn: %d\n", computerMove.col);

            // Make the computer move
            add_element(game, current, computerMove.col);

            // Check if the computer has won
            if (has_won(game, current))
            {
                print_board(game);
                printf("Computer wins!\n");
                break;
            }
        }
        current = other_player(current);
        if (is_full(game))
        {
            print_board(game);
            printf("It's a draw!\n");
        break;
        }
    }
    return 0;
}
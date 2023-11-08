// Team members:KAILA UDAY(22110111),MUKUL MEENA(22110159),SHAURY PATEL(22110241)
#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include "queue.hpp"

struct board {
    int e[3][3];
};

// 0(empty space),1(top),2(bottom),3(left),4(right),5(front),6(back)

void print_board(const board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            printf("%3d", b.e[r][c]);
        }
        printf("\n");
    }
}

void read_board(board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            scanf("%d", &b.e[r][c]);
        }
    }
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

std::tuple<int, int> find_space(const board& b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (b.e[r][c] == 0) return { r, c };
    assert(0);
}

board up(const board& b)
{
    const auto [r,c]= find_space(b);
    if (r == 0) return b;
    board o = b;
    if (o.e[r-1][c]==1){
        o.e[r][c]=6;
    }else if (o.e[r-1][c]==2){
        o.e[r][c]=5;
    }else if (o.e[r-1][c]==5){
        o.e[r][c]=1;
    }else if (o.e[r-1][c]==6){
        o.e[r][c]=2;
    }else{
        o.e[r][c]=o.e[r-1][c];
    }
    o.e[r-1][c]=0;
    return o;
}

board down(const board& b)
{
    const auto [r,c]= find_space(b);
    if (r == 2) return b;
    board o = b;
    if (o.e[r+1][c]==1){
        o.e[r][c]=5;
    }else if (o.e[r+1][c]==2){
        o.e[r][c]=6;
    }else if (o.e[r+1][c]==5){
        o.e[r][c]=2;
    }else if (o.e[r+1][c]==6){
        o.e[r][c]=1;
    }else{
        o.e[r][c]=o.e[r+1][c];
    }
    o.e[r+1][c]=0;
    return o;
}

board left(const board& b)
{
    const auto [r,c]= find_space(b);
    if (c == 0) return b;
    board o = b;
    if (o.e[r][c-1]==1){
        o.e[r][c]=4;
    }else if (o.e[r][c-1]==4){
        o.e[r][c]=2;
    }else if (o.e[r][c-1]==2){
        o.e[r][c]=3;
    }else if (o.e[r][c-1]==3){
        o.e[r][c]=1;
    }else{
        o.e[r][c]=o.e[r][c-1];
    }
    o.e[r][c-1]=0;
    return o;
}

board right(const board& b)
{
    const auto [r,c]= find_space(b);
    if (c == 2) return b;
    board o = b;
    if (o.e[r][c+1]==1){
        o.e[r][c]=3;
    }else if (o.e[r][c+1]==3){
        o.e[r][c]=2;
    }else if (o.e[r][c+1]==2){
        o.e[r][c]=4;
    }else if (o.e[r][c+1]==4){
        o.e[r][c]=1;
    }else{
        o.e[r][c]=o.e[r][c+1];
    }
    o.e[r][c+1]=0;
    return o;
}


bool is_same(const board& a, const board &b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (a.e[r][c] != b.e[r][c]) return false;

    return true;
}

enum move { L = 1, R = 2, U = 3, D = 4 };

int ord(const board& board)
{
    //int seen[10] = { 0 };
    int a = 0;
    int k = 1;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            a += (board.e[r][c] *k);
            k = k*7;
            // int o = 0;
            // for (int i = 1; i < v; ++i) {
            //     if (!seen[i]) { ++o; }
            // }
            // a += o * fact(k);
            // --k;
            // seen[v] = 1;
        }
    }

    return a;
}

#define max_states (40353608)
std::vector<int> solve(const board& src, const board& dest)
{
    queue<board, max_states> q;
    int visited[max_states];
    board parent[max_states];

    enqueue(q, src);
    visited[ord(src)] = L;

    while (!is_empty(q)) {
        board u = dequeue(q);
        if (is_same(u, dest)) {
            std::vector<int> moves;
            board c = u;
            int o = ord(c);
            while (!is_same(c, src)) {
                moves.push_back(visited[o]);
                c = parent[o];
                o = ord(c);
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = up(u);
        board b = down(u);
        board c = left(u);
        board d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);

        if (!visited[aord]) {
            visited[aord] = U;
            parent[aord] = u;
            enqueue(q, a);
        }
        if (!visited[bord]) {
            visited[bord] = D;
            parent[bord] = u;
            enqueue(q, b);
        }
        if (!visited[cord]) {
            visited[cord] = L;
            parent[cord] = u;
            enqueue(q, c);
        }
        if (!visited[dord]) {
            visited[dord] = R;
            parent[dord] = u;
            enqueue(q, d);
        }
    }
    printf("Not solvable");
    return std::vector<int>();
    assert(0);
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case L: printf("L "); break;
        case R: printf("R "); break;
        case U: printf("U "); break;
        case D: printf("D "); break;
        }
    }
    printf("\n");
}

int main()
{
    board src, dest;

    read_board(src);
    read_board(dest);

    auto moves = solve(src, dest);
    print_moves(moves);

    return 0;
}
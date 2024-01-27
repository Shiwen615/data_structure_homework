#include <iostream>
#include <iomanip>

#define n 6
using uint = unsigned int;
constexpr uint nn = n*n;

constexpr int move[8][2] = {{-2, 1},
                            {-1, 2},
                            {1, 2},
                            {2, 1},
                            {2, -1},
                            {1, -2},
                            {-1, -2},
                            {-2, -1}};

void print_board(uint board[][n])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout << std::setw(2) << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void recur_move(uint board[][n], uint round, std::pair<int, int> coor)
{
    if (coor.first < 0 ||
        coor.second < 0 ||
        coor.first >= n ||
        coor.second >= n ||
        board[coor.first][coor.second] != 0)
    {
        return;
    }


    board[coor.first][coor.second] = round;
    // print_board(board);

    if (round == nn)
    {
        print_board(board);
        // return;
        std::exit(0);
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        uint new_board[n][n];
        for (int i = 0; i < n; ++i) {
            std::copy(std::begin(board[i]), std::end(board[i]), std::begin(new_board[i]));
        }
        recur_move(new_board, round+1, {coor.first+move[i][0], coor.second+move[i][1]});
    }
}

int main(int argc, char const *argv[])
{
    // int n = 3;
    uint board[n][n];

    // initialize board to all zero
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            board[i][j] = 0;
        }
    }

    // print_board(board);

    std::pair<int, int> current(0,0);
    recur_move(board, 1, {0,0});


    return 0;
}

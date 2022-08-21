#include <bits/stdc++.h>
#include <chrono>
#include <thread>
typedef long long ll;

void wait(int mili){
    std::this_thread::sleep_for(std::chrono::milliseconds(mili));
}

class Tile
{
private:
    
public:
    int rot;
    int shape;
    std::vector<std::vector<std::vector<int>>> shapes =
    {
    {{0,0}, {1,0}, {2,0}, {2,1}}, // L
    {{0,0}, {0,1}, {1,0}, {1,1}}, // SQUARE
    {{0,0}, {1,0}, {2,0}, {3,0}}, // LONG
    {{0,1}, {1,0}, {1,1}, {1,2}}, // reversed T
    {{0,1}, {1,1}, {2,0}, {2,1}}, // reversed L
    {{0,1}, {0,2}, {1,0}, {1,1}}, // dog right
    {{0,0}, {0,1}, {1,1}, {1,2}}  // dog left
    };
    // default constructor
    Tile(){
        rot = 0;
        shape = -1;
    }
    // parametrized constructor
    Tile(int r, int sh){
        rot = r;
        shape = sh;

    };
    // ~Tile();
};


// whats this????? vv

// Tile::Tile(/* args */)
// {
// }

// Tile::~Tile()
// {
// }

// playing board size:
int board_x = 10;
int board_y = 20;
std::vector<std::vector<int>> original_board(board_y, std::vector<int>(board_x, 0));

void print_board(std::vector<std::vector<int>> &board){
    std::cout << "╔══TETRIS══╗\n";
    for (int r = 0; r < board_y; r++){
        for (int c = 0; c < board_x; c++){
            if (c == 0) std::cout << "║";
            if (board[r][c] == 0){
                std::cout << "·";
            }
            else{
                std::cout << "█";
            }
            if (c == board_x-1) std::cout << "║";
        }
        std::cout << "\n";
    }
    std::cout << "╚══════════╝\n";
}

std::vector<std::vector<int>> place_tile(std::vector<std::vector<int>> &board, Tile &tile, std::vector<int> cursor){
    int x, y;
    auto temp_board = board;
    for (int i = 0; i < tile.shapes[tile.shape].size(); i++){
        x = tile.shapes[tile.shape][i][0];
        y = tile.shapes[tile.shape][i][1];
        if (board[x+cursor[0]][y+cursor[1]] != 1){
            temp_board[x+cursor[0]][y+cursor[1]] = 1;
        }
        else{
            std::cout << "Invalid block position: " << x+cursor[0] << ", " << y+cursor[1] << " .\n";
            return board;
        }
    }
    board = temp_board;
    return board;
}


int main(){
    Tile new_tile(0,1);
    std::vector<int> cursor = {0, 4};
    auto board = original_board;
    print_board(board);
    for (int i = 0; i < 6; i++){
        auto trace_board = original_board;
        trace_board = place_tile(board, new_tile, cursor);
        print_board(trace_board);
        wait(500);
        cursor[0]++;
    }
    

    return 0;
}
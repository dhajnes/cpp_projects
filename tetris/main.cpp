#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <random>
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
    ~Tile(){};
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
    // board = temp_board;
    return temp_board;
}

std::random_device rd;   // init random engine
std::mt19937 rng(rd());  // Mersenne Twister pseudo-random generator of 32-bit number with state size of 19937 bits
std::uniform_int_distribution<int> tile_uni(0,6);
std::uniform_int_distribution<int> random_walk(-1,1);



int main(){
    
    
    auto board = original_board;

    
    
    

    // here a while loop until the block has place to fall
    // i)  has a place to fall, then continnue for the block to fall
    // ii) if not possible for the block fall anymore, place it
    //      - this means that `board = trace_board` and begin the loop again, reset cursor and choose a random tile 

    bool game_on = true;
    int rand_piece_id;
    std::vector<int> cursor;
    while(game_on){ // outer loop, new choice
        cursor = {0, 4};
        rand_piece_id = tile_uni(rng);

        while(1){
            Tile new_tile(0,rand_piece_id);
            int movement_input = random_walk(rng);
            // cursor // TODO add maxing and mining of cursor values so its not possible to get out of bounds
            // possibly use a wrapper function for this that checks that the whole piece wouldnt be out of bounds

        }

    }
    // for (int i = 0; i < 6; i++){
    //     auto trace_board = original_board;
    //     trace_board = place_tile(original_board, new_tile, cursor);
    //     print_board(trace_board);
    //     wait(500);
    //     cursor[0]++;
    // }
    

    return 0;
}
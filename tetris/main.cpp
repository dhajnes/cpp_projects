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
int board_c = 10;
int board_r = 20;
std::vector<std::vector<int>> original_board(board_r, std::vector<int>(board_c, 0));

void print_board(std::vector<std::vector<int>> &board){
    std::cout << "╔══TETRIS══╗\n";
    for (int r = 0; r < board_r; r++){
        for (int c = 0; c < board_c; c++){
            if (c == 0) std::cout << "║";
            if (board[r][c] == 0){
                std::cout << "·";
            }
            else{
                std::cout << "█";
            }
            if (c == board_c-1) std::cout << "║";
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

std::pair<int,int> check_valid_move(Tile tile, std::pair<int,int> cursor, int rotation, std::vector<std::vector<int>> &board, bool recursive_flag){
    /* cursor already moved */

    // auto temp_board = board;
    // auto temp_tile = tile;  // TODO check if this is a deepcopy, may cause problems if not
    // If you hold objects by value then the default copy ctor
    // and assignment operators will do a 'deep copy'.
    // bcz of ^ I take tile by value, not by reference &, it might work, the calss is not large
    tile.rot = rotation;
    std::pair<int, int> correction = {0,0};
    // TODO do rotation here 
    auto tile_pieces = tile.shapes[tile.shape];
    std::pair<int, int> max_deviation = {0,0};

    for (uint i = 0; i < tile_pieces.size(); i++){
        // check if the vertical step would be correct
        if (tile_pieces[i][0] + cursor.first - board_r > 0){
            max_deviation.first = std::max(max_deviation.first, tile_pieces[i][0] + cursor.first - board_r);
            // TODO if this is not correct, the function should signal that the function must be placed now or on the
            // next move
        }  
        else if(board[tile_pieces[i][0] + cursor.first][tile_pieces[i][1] + cursor.second] == 1){
            // max_deviation.first = std::max(max_deviation.first, tile_pieces[i][0]+1)
            auto temp_cursor = cursor;
            if (recursive_flag){
                // TODO finish output from the `check_valid_move` to get maximal number of steps we need to move the tile in order to be valid
                // then choose the smaller move that would satisfy the validity (horizontal vs vertical)
                for(int j = 0; j < 4; j++){
                    temp_cursor.first++;
                    auto disparities = check_valid_move(tile, temp_cursor, rotation, board, false);
                }

                temp_cursor = cursor;
                for(int j = 0; j < 4; j++){
                    temp_cursor.second++;
                    check_valid_move(tile, temp_cursor, rotation, board, false);
                }
            }
        }

        // check if the horisontal step would be correct
        if (tile_pieces[i][1] + cursor.second - board_c > 0){ 
                    check_valid_move(tile, temp_cursor, rotation, board, false);
            max_deviation.second = std::max(max_deviation.second, tile_pieces[i][1] + cursor.second - board_c);

        }

        else if ()
    }

    
}



int main(){
    
    
    auto board = original_board;

    
    
    

    // here a while loop until the block has place to fall
    // i)  has a place to fall, then continnue for the block to fall
    // ii) if not possible for the block fall anymore, place it
    //      - this means that `board = trace_board` and begin the loop again, reset cursor and choose a random tile 

    bool game_on = true;
    int rand_piece_id;
    std::pair<int,int> cursor;
    while(game_on){ // outer loop, new choice
        cursor = {0, 4};
        rand_piece_id = tile_uni(rng);

        while(1){
            Tile new_tile(0,rand_piece_id);
            int movement_increment = random_walk(rng);
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
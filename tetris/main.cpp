#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <random>
#include <Eigen/Dense>
 
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
    std::vector<Eigen::MatrixXd> shapes_mat;
    
    // default constructor
    Tile(){
        rot = 0;
        shape = -1;
        std::vector<Eigen::MatrixXd> shapes_mat(7, Eigen::MatrixXd(2,4));
        shapes_mat[0] << 0, 1, 2, 2, 0, 0, 0, 1; // L
        shapes_mat[1] << 0, 0, 1, 1, 0, 1, 0, 1; // square
        shapes_mat[2] << 0, 1, 2, 3, 0, 0, 0, 0; // long
        shapes_mat[3] << 0, 1, 1, 1, 1, 0, 1, 2; // reversed T
        shapes_mat[4] << 0, 1, 2, 2, 1, 1, 0, 1; // reversed L
        shapes_mat[5] << 0, 0, 1, 1, 1, 2, 0, 1; // dog right
        shapes_mat[6] << 0, 0, 1, 1, 0, 1, 1, 2; // dog left
    }
    // parametrized constructor
    Tile(int r, int sh){
        rot = r;
        shape = sh;
        std::vector<Eigen::MatrixXd> shapes_mat(7, Eigen::MatrixXd(2,4));
        shapes_mat[0] << 0, 1, 2, 2, 0, 0, 0, 1; // L
        shapes_mat[1] << 0, 0, 1, 1, 0, 1, 0, 1; // square
        shapes_mat[2] << 0, 1, 2, 3, 0, 0, 0, 0; // long
        shapes_mat[3] << 0, 1, 1, 1, 1, 0, 1, 2; // reversed T
        shapes_mat[4] << 0, 1, 2, 2, 1, 1, 0, 1; // reversed L
        shapes_mat[5] << 0, 0, 1, 1, 1, 2, 0, 1; // dog right
        shapes_mat[6] << 0, 0, 1, 1, 0, 1, 1, 2; // dog left

    };
    ~Tile(){};
};

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
    int r, c;
    auto temp_board = board;
    for (int i = 0; i < 4; i++){
        r = tile.shapes_mat[tile.shape](i,0);
        c = tile.shapes_mat[tile.shape](i,1);
        if (board[r+cursor[0]][c+cursor[1]] != 1){
            temp_board[r+cursor[0]][c+cursor[1]] = 1;
        }
        else{
            std::cout << "Invalid block position: " << r+cursor[0] << ", " << c+cursor[1] << " .\n";
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

void do_rotation(Eigen::MatrixXd &tile_pieces, int rotation){
    Eigen::MatrixXd rot(2,2);
    rot << 0, -1, 1, 0;  // rot = 90 deg
    for (int i = 0; i < rotation; i++){ // n of rotations
        tile_pieces = rot * tile_pieces;
    }
}

bool check_valid_move(Tile tile, std::pair<int,int> cursor, int rotation, std::vector<std::vector<int>> &board){

    tile.rot = rotation;
    std::pair<int, int> correction = {0,0};
    auto tile_pieces = tile.shapes_mat[tile.shape];
    do_rotation(tile_pieces, rotation);

    // go throught tile pieces ------------------
    for (int c = 0; c < 4; c++){
    
        if (tile_pieces(0,c) + cursor.first - board_r > 0){  // vertical check
        return false;
        }        
        else if (tile_pieces(1,c) + cursor.second - board_c > 0){ // horizontal check
            return false;
        }
        else if(board[tile_pieces(0,c) + cursor.first][tile_pieces(1,c) + cursor.second] == 1){
            return false;
        }
    }
    return true;
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
  

  // TODO test do_rotation function also correct representation of all pieces in the matrix notation
    

    return 0;
}
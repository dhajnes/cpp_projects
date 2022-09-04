#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <ncurses.h>
#include <Eigen/Dense>

#include <stdio.h>

// COMPILE WITH: g++ tetris.cpp -o tetris -lncursesw
 
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
        shapes_mat = std::vector<Eigen::MatrixXd> (7, Eigen::MatrixXd(2,4));
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
        std::cerr << "[Tile-param-const] Parametrized constructor, rot: " << r << ", shape: " << sh << "\n";
        rot = r;
        shape = sh;
        shapes_mat = std::vector<Eigen::MatrixXd> (7, Eigen::MatrixXd(2,4));
        shapes_mat[0] << 0, 1, 2, 2, 0, 0, 0, 1; // L
        shapes_mat[1] << 0, 0, 1, 1, 0, 1, 0, 1; // square
        shapes_mat[2] << 0, 1, 2, 3, 0, 0, 0, 0; // long
        shapes_mat[3] << 0, 1, 1, 1, 1, 0, 1, 2; // reversed T
        shapes_mat[4] << 0, 1, 2, 2, 1, 1, 0, 1; // reversed L
        shapes_mat[5] << 0, 0, 1, 1, 1, 2, 0, 1; // dog right
        shapes_mat[6] << 0, 0, 1, 1, 0, 1, 1, 2; // dog left
        std::cerr << "[Tile-param-const] shapes_mat[0]:\n" << shapes_mat[0] << "\n";

    };
    ~Tile(){};
};

int board_c = 10;
int board_r = 20;
std::vector<std::vector<int>> board(board_r, std::vector<int>(board_c, 0));

std::string print_board(std::vector<std::vector<int>> &board){
    std::string to_display;
    to_display += "+--TETRIS--+\n";
    for (int r = 0; r < board_r; r++){
        for (int c = 0; c < board_c; c++){
            if (c == 0) to_display += "|";
            if (board[r][c] == 0){
                to_display += ".";
            }
            else{
                to_display += "X";
            }
            if (c == board_c-1) to_display += "|";
        }
        to_display += "\n";
    }
    to_display += "+----------+\n";
    return to_display;
}

std::string print_board_alt(std::vector<std::vector<int>> &board){
    std::string to_display;
    to_display += "╔══TETRIS══╗\n";
    for (int r = 0; r < board_r; r++){
        for (int c = 0; c < board_c; c++){
            if (c == 0) to_display += "║";
            if (board[r][c] == 0){
                to_display += "·";
            }
            else{
                to_display += "█";
            }
            if (c == board_c-1) to_display += "║";
        }
        to_display += "\n";
    }
    to_display += "╚══════════╝\n";
    return to_display;
}

std::vector<std::vector<int>> place_tile(std::vector<std::vector<int>> &board, Tile &tile, std::pair<int,int> cursor){
    int r, c;
    std::cerr << "[place_tile] Placing tile.\n";
    auto temp_board = board;
    for (int i = 0; i < 4; i++){
        r = tile.shapes_mat[tile.shape](i,0);
        c = tile.shapes_mat[tile.shape](i,1);
        std::cerr << "[place_tile] Obtained r: " << r << "and c: " << c << "\n";
        if (board[r+cursor.first][c+cursor.second] != 1){
            temp_board[r+cursor.first][c+cursor.second] = 1;
        }
        else{
            std::cout << "Invalid block position: " << r+cursor.first << ", " << c+cursor.second << " .\n";
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
    std::cerr << "[do_rotation] Doing rotation.\n";
    Eigen::MatrixXd rot(2,2);
    rot << 0, -1, 1, 0;  // rot = 90 deg
    for (int i = 0; i < rotation; i++){ // n of rotations
        tile_pieces = rot * tile_pieces;  // TODO this should be zeroed out so there are no negative numbers
    }
}

bool check_valid_move(Tile tile, std::pair<int,int> cursor, int rotation, std::vector<std::vector<int>> &board){

    // tile.rot = rotation;
    std::cerr << "[check_valid_move] Checking valid move.\n";
    // auto tile_pieces = tile.shapes_mat[tile.shape];
    std::cerr << "[check_valid_move] tile.rot: " << tile.rot << " and tile.shape: " << tile.shape << "\n";
    std::cerr << "[check_valid_move] tile.shapes_mat[0]: " << tile.shapes_mat[0] << "\n";
    auto tile_pieces = tile.shapes_mat[0];
    std::cerr << "[check_valid_move] Going for rotation.\n";
    do_rotation(tile_pieces, rotation);

    // go throught tile pieces ------------------
    for (int c = 0; c < 4; c++){
    
        if (tile_pieces(0,c) + cursor.first - board_r > 0){  // vertical check
        return false;
        }        
        else if ((tile_pieces(1,c) + cursor.second - board_c > 0) || (tile_pieces(1,c) + cursor.second < 0)){ // horizontal check
            return false;
        }
        else if(board[tile_pieces(0,c) + cursor.first][tile_pieces(1,c) + cursor.second] == 1){
            return false;
        }
    }
    return true;
}



int main(){
    
    auto falling_board = board;
    bool game_on = true;
    bool episode_on = true;
    int rand_piece_id;
    std::pair<int,int> cursor;

    // ncurses initialization for catching the arrows
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    int row, col;	
    int rot = 0;
    int demanded_rot = rot;
    getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
    
    int ch;
    printw("[ TETRIS ]\n");
    printw("Press E to Exit\n");
    wait(1000);
    std::tuple<Tile, std::pair<int,int>> episode_state;


    while(game_on){ // outer loop, new choice

        
    
        cursor = {0, 4};
        rand_piece_id = tile_uni(rng);
        episode_on = true;

        // one tetris-piece episode
        while(episode_on){
            falling_board = board;
            std::cerr << "[DEBUG] rot:" << rot << " and rand_piece_id: " << rand_piece_id << "\n";
            Tile tetramino(rot, rand_piece_id);
            std::cerr << "[DEBUG] Starting tetramino episode.\n";
            
            // GAME TIMING ==========================
            wait(50);
            timeout(1);
            std::cerr << "[DEBUG] Game timing.\n";
            // GAME INPUT  ==========================

            ch = getch();
            wait(50);
            std::cerr << "[DEBUG] Getting input.\n";
            switch(ch)
            {
            case KEY_UP:
                // Change rotationGame logic i)Game logic i)
                demanded_rot = rot +1;
                demanded_rot = demanded_rot % 4;
                // rot++;
                // rot = rot % 4;
                break;
            case KEY_DOWN:
                // TODO fall faster
                break;
            case KEY_LEFT:
                cursor.second--;
                cursor.second = std::max(cursor.second, 0);
                
                break;
            case KEY_RIGHT:
                cursor.second++;
                cursor.second = std::min(cursor.second, board_c-1);
                break;
            case 'E':
                game_on = false;
                break;
            }

            // GAME LOGIC  ==========================
            // i) check cursor now
            
            if (check_valid_move(tetramino, cursor, demanded_rot, board)){
                std::cerr << "[DEBUG] Game logic i).\n";
                tetramino.rot = demanded_rot;
                episode_state = std::make_tuple(tetramino, cursor);
            }
            else{
                // if this fails it must fail in the beginning -> game over?
                clear();
                printw("    > GAME OVER <    \n");
                wait(1000);
                break;
            }
            // ii) advance the cursor
            cursor.first++;
            if(check_valid_move(tetramino, cursor, demanded_rot, board)){
                std::cerr << "[DEBUG] Game logic ii).\n";
                tetramino.rot = demanded_rot;
                episode_state = std::make_tuple(tetramino, cursor);
            }
            else{
                episode_on = false;
                
            }

            // RENDER OUT  ==========================
            std::cerr << "[DEBUG] Render out.\n";
            if(episode_on){
                //imprinting into "falling board"
                falling_board = place_tile(board, std::get<0>(episode_state), std::get<1>(episode_state));
                printw(print_board(falling_board).c_str());
            }
            else{
                board = place_tile(board, std::get<0>(episode_state), std::get<1>(episode_state));
                printw(print_board(board).c_str());
            }
            
            refresh();
            
            clear();
            

            // while(1){
            //     Tile new_tile(0,rand_piece_id);
            //     int movement_increment = random_walk(rng);
            //     // possibly use a wrapper function for this that checks that the whole piece wouldnt be out of bounds

            // }

        }
        }
        
    endwin();
  

  // TODO test do_rotation function also correct representation of all pieces in the matrix notation
    

    return 0;
}
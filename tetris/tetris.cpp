#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "locale.h"
#include <ncursesw/ncurses.h>
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
        std::cerr << "[Tile-param-const] shapes_mat[sh]:\n" << shapes_mat[sh] << "\n";

    };
    ~Tile(){};
};

int board_c = 10;
int board_r = 20;
std::vector<std::vector<int>> board(board_r, std::vector<int>(board_c, 0));
const char *title_screen = R"(
╔════╗╔╗           ╔════╗         
║╔╗╔╗║║║           ║╔╗╔╗║         
╚╝║║╚╝║╚═╗╔══╗     ╚╝║║╚╝╔═╗╔╗╔══╗
  ║║  ║╔╗║║╔╗║╔═══╗  ║║  ║╔╝╠╣║══╣
 ╔╝╚╗ ║║║║║║═╣╚═══╝ ╔╝╚╗ ║║ ║║╠══║
 ╚══╝ ╚╝╚╝╚══╝      ╚══╝ ╚╝ ╚╝╚══╝
                                  
                                  
)";

void do_rotation(Eigen::MatrixXd &tile_pieces, int rotation){
    std::cerr << "[do_rotation] Doing rotation.\n";
    Eigen::MatrixXd rot(2,2);
    rot << 0, -1, 1, 0;  // rot = 90 deg
    for (int i = 0; i < rotation; i++){ // n of rotations
        tile_pieces = rot * tile_pieces;  // TODO this should be zeroed out so there are no negative numbers
    }
    
    int min_r = 0;
    int min_c = 0;
    for (int i = 0; i < 4; i++){
        if (tile_pieces(0,i) < min_r) min_r = tile_pieces(0,i); // find nonpositive minimum in first row
        if (tile_pieces(1,i) < min_c) min_c = tile_pieces(1,i); // find nonpositive minimum in second row
    }
    for (int i = 0; i < 4; i++){
        tile_pieces(0,i) += -min_r;  // offset first row by -minimum
        tile_pieces(1,i) += -min_c;  // offset second row by -minimum
    }
    
}

std::string print_board(std::vector<std::vector<int>> &board, int row, int col){
    std::string to_display;
    for (int i = 0; i < (row/2)-(board_r+2); i++){
        to_display += "\n";
    }
    std::string spacer;
    for (int i = 0; i < (col/2)-(board_c+2); i++){
        spacer += " ";
    }
    to_display += spacer;
    to_display += "+-THE TRIS-+\n" + spacer;
    for (int r = 0; r < board_r; r++){
        for (int c = 0; c < board_c; c++){
            if (c == 0) to_display += "|";
            if (board[r][c] == 0){
                to_display += ".";
            }
            else if (board[r][c] == 9){
                to_display += "=";
            }
            else{
                to_display += "X";
            }
            if (c == board_c-1) to_display += "|";
        }
        to_display += "\n" + spacer;
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
    std::cerr << "[place_tile] Tile in question:\n" << tile.shapes_mat[tile.shape] << "\n";
    auto tile_pieces = tile.shapes_mat[tile.shape];
    if (tile.rot > 0) do_rotation(tile_pieces, tile.rot);
    auto temp_board = board;
    for (int i = 0; i < 4; i++){
        r = tile_pieces(0,i);
        c = tile_pieces(1,i);
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

bool check_valid_move(Tile tile, std::pair<int,int> cursor, int rotation, std::vector<std::vector<int>> &board){

    // tile.rot = rotation;
    std::cerr << "[check_valid_move] Checking valid move.\n";
    std::cerr << "[check_valid_move] tile.rot: " << tile.rot << " and tile.shape: " << tile.shape << "\n";
    std::cerr << "[check_valid_move] tile.shapes_mat[tile.shape]: \n" << tile.shapes_mat[tile.shape] << "\n";
    auto tile_pieces = tile.shapes_mat[tile.shape];
    std::cerr << "[check_valid_move] Going for rotation.\n";
    if (rotation > 0) do_rotation(tile_pieces, rotation);
    

    // go throught tile pieces ------------------
    for (int i = 0; i < 4; i++){
        std::cerr << "------------------\n";
        std::cerr << "[check_valid_move] tile pieces:\n" << tile_pieces(0,i) << "\n" << tile_pieces(1,i) << "\n";
        std::cerr << "[check_valid_move] cursor:\n" << cursor.first << "\n" << cursor.second << "\n";
        std::cerr << "[check_valid_move] board dimensions [r,c].T:\n" << board_r << "\n" << board_c << "\n";
        std::cerr << "[check_valid_move] 1) tile_pieces(0, i) + cursor.first >= board_r |" << tile_pieces(0, i) + cursor.first << " >= " << board_r << "\n";
        std::cerr << "[check_valid_move] 2.1) tile_pieces(1, i) + cursor.second >= board_c |" << tile_pieces(1, i) + cursor.second << " >= " << board_c << "\n";
        std::cerr << "[check_valid_move] 2.2) || tile_pieces(1, i) + cursor.second < 0 |" << tile_pieces(1, i) + cursor.second << " < " << 0 << "\n";
        // std::cerr << "[check_valid_move] 3) board[tile_pieces(0, i) + cursor.first][tile_pieces(1, i) + cursor.second] == 1 |" << "board[" << tile_pieces(0, i) + cursor.first << "][ " << tile_pieces(1, i) + cursor.second << "] == " << board[tile_pieces(0, i) + cursor.first][tile_pieces(1, i) + cursor.second] << "?= 1\n";
        
        if (tile_pieces(0, i) + cursor.first >= board_r){  // vertical check
            return false;
        }        
        
        else if ((tile_pieces(1, i) + cursor.second >= board_c) || (tile_pieces(1, i) + cursor.second < 0)){ // horizontal check
            return false;
        }
        else if(board[tile_pieces(0, i) + cursor.first][tile_pieces(1, i) + cursor.second] == 1){
            return false;
        }
    }
    std::cerr << "------------------\n";
    return true;
}

std::pair<bool, std::vector<std::vector<int>>> check_for_tetris(std::vector<std::vector<int>> &board){
    std::cerr << "[check_for_tetris] Checking for tetris.\n";
    std::vector<std::vector<int>> new_board(board_r, std::vector<int>(board_c, 0));
    auto print_board = board;
    std::vector<bool> tetris_rows(board_r, false);
    std::pair<bool, std::vector<std::vector<int>>> output;
    std::vector<int> tetris_row_indices;
    bool is_tetris = false;
    // find 
    for(int r = 0; r < board_r; r++){
        for (int c = 0; c < board_c; c++){
            if (board[r][c] != 1){
                break;
            } 
            if (c == board_c-1){
                tetris_rows[r] = true;
                is_tetris = true;
            }
        }
    }
    for (uint i = 0; i < tetris_rows.size(); i++){
        if (tetris_rows[i] == true) tetris_row_indices.push_back(i);
    }

    
    
    if(is_tetris){
        int r_cnt = board_r-1;
        for (int r = board_r-1; r >=0; r--){
            if (tetris_rows[r]) continue;
            else {
                for (int c = 0; c < board_c; c++){
                    new_board[r_cnt][c] = board[r][c];
                }
                r_cnt--;
            }
        }
        for (uint i = 0; i < tetris_row_indices.size(); i++){
            for(int c = 0; c < board_c; c++){
                print_board[tetris_row_indices[i]][c] = 9;
            }
        }
        board = new_board;
    }

    output.first = is_tetris;
    output.second = print_board;
    return output;
}



int main(){
    
    setlocale(LC_ALL, "");
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
    move(row/2-10, col/2-30);
    printw(title_screen);
    // printw("       [ THE TRIS ]\n");
    printw("     Press E to Exit\n");
    refresh();
    wait(2000);
    
    printw(" ~ Made by Andrej Kruzliak ~");
    refresh();
    wait(2000);
    
    std::tuple<Tile, std::pair<int,int>> episode_state;


    while(game_on){ // outer loop, new choice

        
    
        cursor = {0, 4};
        auto demanded_cursor = cursor;
        rand_piece_id = tile_uni(rng);
        episode_on = true;

        // one tetris-piece episode
        std::cerr << "[DEBUG] Starting tetramino episode.\n";
        int render_timer = 0;
        while(episode_on){
            render_timer++;
            falling_board = board;
            std::cerr << "[DEBUG] rot:" << rot << " and rand_piece_id: " << rand_piece_id << "\n";
            Tile tetramino(rot, rand_piece_id);
            
            
            // GAME TIMING ==========================
            wait(30);
            timeout(1);
            std::cerr << "[DEBUG] Game timing.\n";
            // GAME INPUT  ==========================

            ch = getch();
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
                demanded_cursor.second = cursor.second - 1;
                // cursor.second--;
                demanded_cursor.second = std::max(demanded_cursor.second, 0);
                
                break;
            case KEY_RIGHT:
                demanded_cursor.second = cursor.second + 1;
                // cursor.second++;
                demanded_cursor.second = std::min(demanded_cursor.second, board_c-1);
                break;
            case 'E':
                game_on = false;
                endwin();
                exit(0);
                break;
            }

            // GAME LOGIC  ==========================
            // i) check cursor now
            if (render_timer > 10){
                clear();
                if (check_valid_move(tetramino, demanded_cursor, demanded_rot, board)){
                    std::cerr << "[DEBUG] Game logic i).\n";
                    tetramino.rot = demanded_rot;
                    rot = demanded_rot;
                    episode_state = std::make_tuple(tetramino, demanded_cursor);
                    cursor.first = demanded_cursor.first;
                    cursor.second = demanded_cursor.second;
                }
                else{
                    episode_state = std::make_tuple(tetramino, cursor);
                    demanded_cursor.first = cursor.first;
                    demanded_cursor.second = cursor.second;
                    // if this fails it must fail in the beginning -> game over?
                    // clear();
                    // printw("    > GAME OVER <    \n");
                    // wait(1000);
                    // break;
                }
                // ii) advance the cursor
                demanded_cursor.first++;
                if(check_valid_move(tetramino, demanded_cursor, demanded_rot, board)){
                    std::cerr << "[DEBUG] Game logic ii).\n";
                    tetramino.rot = demanded_rot;
                    rot = demanded_rot;
                    episode_state = std::make_tuple(tetramino, demanded_cursor);
                    cursor.first = demanded_cursor.first;
                    cursor.second = demanded_cursor.second;
                    
                }
                else{
                    episode_on = false;
                    
                }

            // RENDER OUT  ==========================
            
                std::cerr << "[DEBUG] Render out.\n";
                
                if(episode_on){
                    //imprinting into "falling board"
                    falling_board = place_tile(board, std::get<0>(episode_state), std::get<1>(episode_state));
                    printw(print_board(falling_board, row, col).c_str());
                }
                else{
                    board = place_tile(board, std::get<0>(episode_state), std::get<1>(episode_state));

                    auto tetris_check_pair = check_for_tetris(board);
                    if (tetris_check_pair.first){
                        printw(print_board(tetris_check_pair.second, row, col).c_str());   
                        refresh(); 
                        wait(500);
                        clear();
                        
                    }
                    printw(print_board(board, row, col).c_str());
                }
                refresh();
                
                render_timer = 0;    
            }
            
            
            


        }
    }
        
    endwin();
  
    return 0;
}
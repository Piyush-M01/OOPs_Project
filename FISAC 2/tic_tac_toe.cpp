#include <iostream>
#include "tic_tac.hpp"

using namespace std;

void Board::disp_board()    // Pure virtual functions definition
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << Board::board[i][j];    // prints the value of the cell of Board::board matrix
            if (j < 2) cout << " | ";   // adding a vertical bar after every array value
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

void Board::disp_coords()   // Pure virtual functions definition
{
    cout<<"\n";
    cout<<"Coordinates of each cell \n";
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "("<<i+1<<","<<j+1<<")";
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "----------------------" << endl;
    }
    cout<<"\n";
}

Board::Board():size(3)  // initializes the size to be 3 using initializer list
{
    moves = new string[9];    // dynamically creating new array
    count = 0;  //  stores the number of moves made by each player
}

void Board::set_position(int r, int c, char p)
{
    Board::board[r][c] = p; //  updating the board cells with player alias stored in variabl 'p'
}

Board::~Board()
{
    delete []moves; // virtual destructor deleting the instance of moves array so that there is no memory leak
}

void Board::display()   // virtual function
{
    cout<<"size variable displayed from base class "<<size<<"\n";

}

Game::Game():Board()   // base class initialization
{
    q = new int[10];    // for demonstration purpose only
    currPlayer = 'X';
    pos = 0;
}
Game::~Game()
{
    cout<<"Destructor called as the Parent class destructor is virtual\n";
    delete []q;     // if not for virtual destructor of parent class
                    // this destructor would not be called, resulting in memory leak
}
void Game::display(){   // non virtual display function

    cout<<"Protected Size variable is accessible to derived class "<<size<<"\n";
    cout<<"Size varible was displayed from derived class\n";
}

void Game::update(int r,int c)  // updates the cells of board 
{
    q[pos++] = pos; // updates the position and sets the number of times class has been called in each index
    moves[count++] = to_string(r)+" * "+to_string(c);
    set_position(r,c,currPlayer);   // uses Board class set method to update the board
}

void player_x::update(int r, int c, char p) // function overloading -- static polymorphism
{
    moves[count++] = to_string(r)+" * "+to_string(c);
    set_position(r,c,p);    // uses Board class set method to update the board
}

void player_o::update(int r, int c)   // function overriding
{
    moves[count++] = to_string(r)+" * "+to_string(c);
    currPlayer = 'O';   // sets player name as 'O'
    Game::update(r,c);  // uses Board class set method to update the board
}

void TicTacToe::Play()
{
    cout << "Welcome to Tic Tac Toe!\n";

    player_x p1;    // player 1
    player_o p2;    // player 2
    Game gm;        // game object to play various functions of the game

    for (int move = 1; move <= 9; move++) {

        gm.disp_coords();   // displaying the rows and column number for the board cell

        if(move%2 != 0){    // if odd position, player 1 makes the move
            currPlayer = 'X';
            cout << "Player " << currPlayer << ", enter row and column (e.g., 1 2): ";
            cin >> row >> col;  
            // Check if the move is valid
            if (row < 1 || row > 3 || col < 1 || col > 3) {
                cout<<row<<" "<<col<<endl;
                cout << "Invalid move! Try again." << endl;
                move--;  // Retry the same move
                continue;
            }
            p1.update(row-1,col-1,'X');
            gm.disp_board();
            // Check if the current player has won
            if (gm.check(currPlayer)) {
                cout << "Player " << currPlayer << " wins! Congratulations!" << endl;
                break;
            }
        }
        else{   // if even, player 2 makes the move
            currPlayer = 'O';
            cout << "Player " << currPlayer << ", enter row and column (e.g., 1 2): ";
            cin >> row >> col;
            // Check if the move is valid
            if (row < 1 || row > 3 || col < 1 || col > 3 ) {
                cout<<row<<" "<<col<<endl;
                cout << "Invalid move! Try again." << endl;
                move--;  // Retry the same move
                continue;
            }
            p2.update(row-1,col-1);
            gm.disp_board();
            // Check if the current player has won
            if (gm.check(currPlayer)) {
                cout << "Player " << currPlayer << " wins! Congratulations!" << endl;
                break;
            }
        }
    }

    // If no one has won after 9 moves, it's a draw
    if (gm.check('X') == false && gm.check('O') == false) {
        cout << "It's a draw! The game is over." << endl;
    }
}

bool Game::check(char player)   // calls the checkWin function of the Board class to check for winner
{
    return checkWin(player);
}

bool Board::checkWin(char player){

    for (int i = 0; i < 3; i++) {

        // checks the possibilities of victory for players and returns true or false based on it

        if (Board::board[i][0] == player && Board::board[i][1] == player && Board::board[i][2] == player) return true;
        if (Board::board[0][i] == player && Board::board[1][i] == player && Board::board[2][i] == player) return true;
    }

    if (Board::board[0][0] == player && Board::board[1][1] == player && Board::board[2][2] == player) return true;
    if (Board::board[0][2] == player && Board::board[1][1] == player && Board::board[2][0] == player) return true;
    
    return false;

}
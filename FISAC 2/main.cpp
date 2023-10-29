#include "tic_tac_toe.cpp"
using namespace std;

int main()
{
    Game *ob;
    player_o ob1;
    ob = &ob1; // Base class pointer pointing to derived class object
    ob->update(0,0); // ignores overriding by derived class

    Board b1;
    b1.display();   // calls base class display

    Game g;
    Board &b = g;
    b.display();    // calls derived class display
    b.Board::display(); // forcibly calls base class display

    TicTacToe game;     // Tic tac toe class object to start playing the game
    game.Play();       // calls the Play() function to perform game operations
    return 0;
}

// inheritance followed: Hybrid - combination of hierarchical and multilevel inheritance
//      Display_Board -- Abstract Class with pure virtual functions
//          |
//        Board 
//          |
//        Game
//        /     |
//    player_o  player_x

// TicTacToe class to play the game. It is neither inherited nor inherits any class
# pragma once

#include<iostream>
using namespace std;

class Display_Board{    // Abstract class

    public:
        virtual void disp_board() = 0;      // Pure virtual functions
        virtual void disp_coords() = 0;     // Pure virtual functions

};

class Board: public Display_Board{

    private:
        static char board[3][3];    // static board so that all the classes update the same instance of board

    protected:      //  protected data members which can be accessed by the derived classes only
        string *moves;
        int count;
        const int size;
    
    public:
        Board();
        virtual ~Board();   // virtual destructor
        virtual void display(); // virtual function
        void disp_coords(); // abstract class functions declarations
        void disp_board();  // abstract class functions declarations
        bool checkWin(char player);
        void set_position(int r, int c, char p);

};


class Game: public Board{

    protected:  //  protected data members which can be accessed by the derived classes only
        char currPlayer;
        int *q; // stores number of times each class calls the Game class
        int pos;
    public:
        Game();
        void update(int r, int c);
        void display();
        bool check(char player);
        ~Game();

};

class player_x: public virtual Game{    // virtual base class 
    
    public:
        void update(int r, int c, char p); // function overloading -- static polymorphism
};

class player_o:public virtual Game{     // virtual base class 

    public:
        void update(int r, int c);   // function overriding
};

class TicTacToe{

    private:
        int row;
        int col;
        char currPlayer;
    public:
        void Play();

};

char Board::board[3][3];

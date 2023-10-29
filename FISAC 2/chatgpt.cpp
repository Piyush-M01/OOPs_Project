// using hierarchical inheritance

#include <iostream>

// Concept: Base class with a pure virtual function
class Player {
public:
    Player(std::string name, char symbol) : name(name), symbol(symbol) {}

    // Concept: Pure virtual function for function overriding
    virtual void makeMove(char board[3][3]) = 0;

    char getSymbol() const {
        return symbol;
    }

    // Concept: Virtual destructor to prevent memory leaks
    virtual ~Player() {
        std::cout << "Player " << name << " has been removed." << std::endl;
    }

protected:
    // Concept: Protected data member
    std::string name;
    char symbol;
};

// Concept: Inheritance, derived from the Player class
class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name, char symbol) : Player(name, symbol) {}

    // Concept: Function overriding
    void makeMove(char board[3][3]) override {
        int row, col;
        do {
            std::cout << "Player " << name << ", enter your move (row and column): ";
            std::cin >> row >> col;
        } while (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ');

        board[row][col] = symbol;
    }
};

// Concept: Inheritance, derived from the Player class
class ComputerPlayer : public Player {
public:
    ComputerPlayer(std::string name, char symbol) : Player(name, symbol) {}

    // Concept: Function overriding
    void makeMove(char board[3][3]) override {
        // Implement computer AI to make a move
        int row, col;
        do {
            // Random move for simplicity
            row = rand() % 3;
            col = rand() % 3;
        } while (board[row][col] != ' ');

        board[row][col] = symbol;
    }
};

// Concept: Inheritance, derived from the Player class
class TicTacToeGame {
public:
TicTacToeGame(Player& p1, Player& p2) : player1(p1), player2(p2), currentPlayer(&player1) {}

    void play() {
        char board[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
        bool gameWon = false;
        int moves = 0;

        while (!gameWon && moves < 9) {
            printBoard(board);
            currentPlayer->makeMove(board);
            gameWon = checkWin(board, currentPlayer->getSymbol());
            currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
            moves++;
        }

        printBoard(board);
        if (gameWon) {
            std::cout << "Player " << currentPlayer->getSymbol() << " wins!" << std::endl;
        } else {
            std::cout << "It's a draw!" << std::endl;
        }
    }

private:
    Player& player1;
    Player& player2;
    Player* currentPlayer;

    // Function to display the current state of the Tic-Tac-Toe board
    void printBoard(const char board[3][3]) {
        std::cout << "Current board:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << board[i][j];
                if (j < 2) std::cout << " | ";
            }
            std::cout << std::endl;
            if (i < 2) std::cout << "---------\n";
        }
        std::cout << std::endl;
    }

    // Function to check if a player has won
    bool checkWin(const char board[3][3], char symbol) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
        }
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
        return false;
    }
};

int main() {
    HumanPlayer player1("Alice", 'X');
    ComputerPlayer player2("Computer", 'O');

    TicTacToeGame game(player1, player2);
    game.play();

    return 0;

     // Use polymorphic assignment with pointers to the base class
    // Player* p1 = &player1;
    // Player* p2 = &player2;

    // TicTacToeGame game(*p1, *p2);
    // game.play();

    return 0;
}

#include <iostream>
#include <string>
#include <typeinfo>
#include <limits>
#include <stdio.h>

using namespace std;

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int gamestate = -2; //-2 means "game isn't finished yet, 0 = draw, 1 = O won, -1 = X won

void printBoard()
{
    string h_line = "_____|_____|_____";
    string v_line = "     |     |     ";
    string indent = "\t\t\t";

    cout << "\n\n\n";
    cout << "\t\t   Player 1 (X) - Player 2 (O)   \n\n\n"
         << endl;
    cout << indent << v_line << endl;
    cout << indent << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;
    cout << indent << h_line << endl;
    cout << indent << v_line << endl;
    cout << indent << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;
    cout << indent << h_line << endl;
    cout << indent << v_line << endl;
    cout << indent << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;
    cout << indent << v_line << endl;
    cout << "\n\n\n";
}

int numOfEmptyCells() {

    int nOfEmptyCells = 9;
    for (int i = 0; i<3; i++){
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') nOfEmptyCells--;
        }
    }
    return nOfEmptyCells;
}
bool isValidChoice(int position)
{
    if (position < 1 || position > 9)
        return false;

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] != ' ')
        return false;

    return true;
}

void makeMove(int position, int player)
{
    char symbol = player == 0 ? 'X' : 'O';

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    board[row][col] = symbol;
   
}

bool isWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][2] == board[i][0]) // row win
        {
            gamestate = -1 ? board[i][0] == 'X' : +1;
            return true;
        }
        else if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[2][i] == board[0][i]) // column win
        {
            gamestate = -1 ? board[0][i] == 'X' : +1;
            return true;
        }
    }

    if (board[0][0] != ' ' && board[1][1] == board[0][0] && board[2][2] == board[0][0])
    {
        gamestate = -1 ? board[0][0] == 'X' : +1;
        return true;
    }
    else if (board[0][2] != ' ' && board[1][1] == board[0][2] && board[2][0] == board[0][2]){
        gamestate = -1 ? board[0][2] == 'X' : +1;
        return true;
    }
    return false;
}

bool isDraw()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

void printDots(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << ".";
        system("sleep 0.5");
    }
}
// We should have Memoized, we ain't no stupid! => alpha-beta Pruning
int MiniMax(char nodes[3][3], int depth, bool maximizingPlayer) {
    if (depth == 0 || gamestate != -2)
        return gamestate;
    else if (maximizingPlayer) {
        int value = -10000000;
        for (int i; i < depth; i++) { //WTF does Depth mean? Depth should be the number of empty cells!
            // make a move and update gamestate!
            value = std::max(value, MiniMax(nodes, depth - 1, false));
        }
        return value;
    }
    else {
        int value = +1000000;
        for (int i; i < depth; i++) {
            value = std::min(value, MiniMax(nodes, depth - 1, false));
        }
        return value;
    }
}

// we don't need alpha-beta pruning. We, Because searching is "Easy", as the heuristic is not good!
void aiMove() {
    // making a random move
    for (int i; i < 9; i++) {
        int move = 1 + (rand() % 9);
        if (isValidChoice(move)) {
            makeMove(move, 2);
            if (MiniMax(board, 9, false) == 1) //why in the world 9?!?! It should be nOfEmptyCells!
                return;
        }
    }
}

void playGame(int mode)
{
    int choice = 0;
    int player = 0;
    int winner = 0; //if mode is 1, player 2 becomes the Computer
    bool draw = false;
    if (mode == 1)
        player = 2; //technically, player 3 is the ai... whatever!
    while (true)
    {
        system("cls");
        printBoard(); 
        if (winner != 0)
        {
            cout << "Player " << winner << " Won! ";
            printDots(3);
            break;
        }
        else if (draw)
        {
            cout << "Draw! ";
            printDots(3);
            break;
        }

        cout << "Player " << player + 1 << " Turn: ";
        if ((player + 1) / 3 == 1 && mode == 1)
            aiMove();
        else 
            cin >> choice;
        if (isValidChoice(choice))
        {
            makeMove(choice, player);
        }
        else
        {
            cout << "Invalid Choice! ";
            printDots(3);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                '\n');
            cin.clear();
            continue;
        }
        if (isWinner())
            winner = player + 1;
        else if (isDraw())
            draw = true;
        player = (player + 1) % 2;
        choice = 0;
    }
}

int main(int argc, char* argv[])
{
    int mode = 1; //1 is for computer vs human
    playGame(mode);

    return 0;
}
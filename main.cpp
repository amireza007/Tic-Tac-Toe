#include <iostream>
#include <string.h>

using namespace std;

int SIZE = 3;
char board[3][3] = {{'X', 'X', 'O'}, {'.', 'X', '.'}, {'.', '.', 'X'}};

void printBoard()
{
    string h_line = "_____|_____|_____";
    string v_line = "     |     |     ";
    string indent = "\t\t\t";

    cout << indent << v_line << endl;
    cout << indent << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;
    cout << indent << h_line << endl;
    cout << indent << v_line << endl;
    cout << indent << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;
    cout << indent << h_line << endl;
    cout << indent << v_line << endl;
    cout << indent << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;
    cout << indent << v_line << endl;
}

bool isValidChoice(int position)
{
    return true;
}

void makeMove(int position, int player)
{
}

bool isWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != '.' and board[i][0] == board[i][1] != '.' and board[i][2] == board[i][0])
        {
            return true;
        }
        else if (board[0][i] != '.' and board[0][i] == board[1][i] != '.' and board[2][i] == board[0][i])
        {
            return true;
        }
    }

    if (board[0][0] != '.' and board[1][1] == board[0][0] != '.' and board[2][2] == board[0][0])
        return true;
    else if (board[0][2] != '.' and board[1][1] == board[0][0] != '.' and board[2][0] == board[0][0])
        return true;

    return false;
}

void playGame()
{
    int choice = 0;
    int player = 0;
    int winner = 0;
    while (true)
    {
        cin >> choice;
        if (isValidChoice(choice))
        {
            makeMove(choice, player);
            printBoard();
            if (isWinner())
            {
            }
        }
        else
        {
            cout << "";
        }
    }
}

int main()
{
    cout << isWinner();
    return 0;
}
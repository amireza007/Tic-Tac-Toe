#include <iostream>
#include <string.h>

using namespace std;

int SIZE = 3;
char board[3][3] = {{'X', '.', '.'}, {'.', '.', '.'}, {'.', '.', '.'}};

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

int main()
{
    printBoard();
    return 0;
}
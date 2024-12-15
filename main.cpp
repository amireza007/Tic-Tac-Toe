#include <iostream>
#include <string>
#include <typeinfo>
#include <limits>

using namespace std;

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

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
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][2] == board[i][0])
        {
            return true;
        }
        else if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[2][i] == board[0][i])
        {
            return true;
        }
    }

    if (board[0][0] != ' ' && board[1][1] == board[0][0] && board[2][2] == board[0][0])
        return true;
    else if (board[0][2] != ' ' && board[1][1] == board[0][2] && board[2][0] == board[0][2])
        return true;

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

void playGame()
{
    int choice = 0;
    int player = 0;
    int winner = 0;
    bool draw = false;
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
    playGame();
    return 0;
}
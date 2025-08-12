#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <array>
using namespace std;
#define INF 100000

char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
int num_of_visited_nodes = 0;
int num_of_visited_nodes2 = 0;
int num_of_empty_cells = 9;

vector<int> emptyCellsList()
{
    vector<int> result;
    for (int i = 1; i <= 9; i++) {
        if (board[(i - 1) / 3][(i - 1) % 3] == ' ')
            result.push_back(i);
    }
    return result;
}

void printBoard()
{
    string h_line = "_____|_____|_____";
    string v_line = "     |     |     ";
    string indent = "\t\t\t";

    cout << "\n\n\n";
    cout << "\t\t   Player 1 (O) - Player 2 (X)   \n\n\n"
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

void makeMove(int position, int player, char board[3][3])
{
    char symbol = player == 1 ? 'X' : 'O';

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    board[row][col] = symbol;
}


int isWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][2] == board[i][0])
        {
            if (board[i][0] == 'X')
                return 1;
            else
                return -1;
        }
        else if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[2][i] == board[0][i])
        {
            if (board[0][i] == 'X')
                return 1;
            else
                return -1;
        }
    }

    if (board[0][0] != ' ' && board[1][1] == board[0][0] && board[2][2] == board[0][0]) {
        if (board[0][0] == 'X')
            return 1;
        else
            return -1;
    }
        
        
    else if (board[0][2] != ' ' && board[1][1] == board[0][2] && board[2][0] == board[0][2]) {
        if (board[0][2] == 'X')
            return 1;
        else
            return -1;
    }

    return 0;
}

bool isDraw()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;

    return true;
}
int bestmaxPos;
int bestminPos;


int MiniMax(bool maximizingPlayer, int depth, char board[3][3])
{
    int utility;
    if (depth == 0 || isWinner()) {
        return isWinner();
    }
    if (maximizingPlayer) {
        utility = -INF;
        int position;
        for (int i : emptyCellsList()) {
            makeMove(i, 1, board);
            num_of_visited_nodes++;
            int temp = utility;

            utility = max(utility,MiniMax(false, depth - 1, board));
            
            if (temp < utility)
                position = i;
            board[(i - 1) / 3][(i - 1) % 3] = ' '; //undo the move
        }
        bestmaxPos = position;
        return utility;
    }
    if(!maximizingPlayer) {//minimizing player, i.e. 'O'
        int utility = INF;
        int position;
        for (int i : emptyCellsList()) {
            int temp2 = utility;
            makeMove(i, 0, board);
            num_of_visited_nodes++;
            utility = min(utility,MiniMax(true, depth - 1, board));            
            if (temp2 > utility)
                position = i;
            board[(i - 1) / 3][(i - 1) % 3] = ' '; //undo the move
        }
        bestminPos = position;
        return utility;
    }
}


int alphaBetaPrune(bool maximizingPlayer, int depth, char board[3][3], int alpha = -INF, int beta = INF)
{
    int utility;

    if (depth == 0 || isWinner()) {
        return isWinner();
    }
    if (maximizingPlayer) {
        utility = -INF;
        int position;
        for (int i : emptyCellsList()) {
            makeMove(i, 1, board);
            num_of_visited_nodes2++;
            int temp = utility;

            utility = max(utility, alphaBetaPrune(false, depth - 1, board,alpha,beta));
            board[(i - 1) / 3][(i - 1) % 3] = ' '; //undo the move
            if (utility >= beta)
                break;
            alpha = max(alpha, utility);
            if (temp < utility)
                position = i;
        }
        bestmaxPos = position;
        return utility;
    }
    if (!maximizingPlayer) {//minimizing player, i.e. 'O'
        int utility = INF;
        int position;
        for (int i : emptyCellsList()) {
            int temp2 = utility;
            makeMove(i, 0, board);
            num_of_visited_nodes2++;
            utility = min(utility, alphaBetaPrune(true, depth - 1, board, alpha, beta));
            board[(i - 1) / 3][(i - 1) % 3] = ' '; //undo the move
            if (utility <= alpha)
                break;
            beta = min(beta, utility);
            if (temp2 > utility)
                position = i;
        }
        bestminPos = position;
        return utility;
    }
}

void printDots(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << ".";
        system("timeout 1");
    }
}

void playGame()
{
    int choice = 0; 
    int player = 0; //'X' is maximizingPlayer (i.e. 'X' = 1)
    int winner = 0;
    bool HumansFirst = true;
    bool Ai_mode = false;
    bool draw = false;
    int MiniMaxChoice = NULL;
    int alphabetaChoice = NULL;
    num_of_visited_nodes = 0;
    num_of_visited_nodes2 = 0;
    cout << "type 0 for <Human vs Human> and 1 for <Human vs Ai>: ";
    cin >> Ai_mode;
    if (Ai_mode) {
        cout << "type 1 if you wanna be the first to play; 0 otherwise: ";
        cin >> HumansFirst;
        if (!HumansFirst) {
            cout << "\t\t\tHUMAN VS Ai" << endl;
            player = 1;
            MiniMax(player == 1 ? true : false, size(emptyCellsList()), board);
            MiniMaxChoice = bestmaxPos;

            alphaBetaPrune(player == 1 ? true : false, size(emptyCellsList()), board);
            alphabetaChoice = bestmaxPos;

            makeMove(bestmaxPos, player, board);
            player = (player + 1) % 2;
        }
    }
    while (true)
    {
        system("cls");
        printBoard();
        if (Ai_mode) {
            cout << "\t\t\tHUMAN VS Ai" << endl;
            
            cout << "number of visited nodes by Minimax: " << num_of_visited_nodes << endl;
            cout << "number of nodes visited by Alpha-Beta prunning: " << num_of_visited_nodes2 << endl;
            if (num_of_visited_nodes != 0)
                cout << "=>>>>>> " << 100 - 100*((float) num_of_visited_nodes2/num_of_visited_nodes) << "% reduction!!" << endl;
            cout << "MiniMax choice: " << MiniMaxChoice << endl;
            cout << "Alpha-Beta prunning choice: " << alphabetaChoice << endl;
        }
        else {
            cout << "\t\t\tHUMAN VS HUMAN" << endl;
        }
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
            
            makeMove(choice, player, board);
            
            if (Ai_mode) {
                num_of_visited_nodes = 0;
                num_of_visited_nodes2 = 0;
                player = (player + 1) % 2;
                MiniMax(player == 1 ? true : false, size(emptyCellsList()), board);
                MiniMaxChoice = bestmaxPos;

                alphaBetaPrune(player == 1 ? true : false, size(emptyCellsList()), board);
                alphabetaChoice = bestmaxPos;

                makeMove(bestmaxPos, player, board);
                player = (player + 1) % 2;
            }
        }

        else
        {
            cout << "Invalid Choice! ";
            printDots(3);
            continue;
        }

        if (isWinner() != 0)
            winner = player + 1;
        else if (isDraw())
            draw = true;

        if (!Ai_mode)
            player = (player + 1) % 2;
        
    }
}

int main()
{   
    playGame();
    return 0;
}
#include <iostream>
#include <cstdlib>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::abs;

struct square{
    bool isOccupied;
    bool kinged;
    char player;
};

struct PlayerMove{
    int r1, r2, c1, c2;
};

void displayBoard(square board[10][10]);
bool validateMove(square board[10][10], PlayerMove playerMove, bool playerTurn, bool firstMove);
bool makeMove(square board[10][10], PlayerMove playerMove, bool playerTurn);
PlayerMove getMove(bool firstMove, PlayerMove playerMove, bool playerTurn);
bool checkForWin(square board[10][10]);

void checkers(){
    //initialize board
    square board[10][10];
    square even;
    square odd;
    even.isOccupied = false;
    even.kinged = false;
    even.player = 0;
    odd.isOccupied = false;
    odd.kinged = false;
    odd.player = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(i % 2 == 0){
                if(j % 2 == 0){
                    board[i][j] = even;
                }
                else{
                    board[i][j] = odd;
                    if(i > 5 || i < 4){
                        board[i][j].isOccupied = true;
                    }
                }
            }
            else{
                if(j % 2 == 0){
                    board[i][j] = odd;
                    if(i > 5 || i < 4){
                        board[i][j].isOccupied = true;
                    }
                }
                else{
                    board[i][j] = even;
                }
            }

            if(i < 5){
                board[i][j].player = 0;
            }
            else{
                board[i][j].player = 1;
            }
        }
    }

    bool executing = true;
    bool playerTurn = false; //False is Player 1 (top)'s turn, true is player 2 (bottom)'s turn.
    bool firstMove = true;
    bool changeTurn = false;
    displayBoard(board);
    firstMove = true;
    while(executing){
        PlayerMove playerMove;
        changeTurn = false;
        firstMove = true;
        while(!changeTurn){
            do{
                playerMove = getMove(firstMove, playerMove, playerTurn);
            }while(!validateMove(board, playerMove, playerTurn, firstMove)); //{0,0,0,0} changes turn, so it is valid
            changeTurn = makeMove(board, playerMove, playerTurn);
            firstMove = false;
            //Shift array left by two, and ask for new destination until player declines and playerTurn changes
            playerMove.r1 = playerMove.r2;
            playerMove.c1 = playerMove.c2;
            displayBoard(board);
        }
        playerTurn = !playerTurn;

        executing = checkForWin(board);
    }
}

void displayBoard(square board[10][10]){
//display board
    //clear screen
    std::system("cls");
    /*for(int i = 0; i < 45; i++){
        cout << endl;
    }*/
    //Top edge
    cout << endl << "  " << char(213);
        for(int k = 0; k < 19; k++){
            if(k % 2 != 0){
                cout << char(209);
            }
            else{
                cout << char(205);
            }
        }
    cout << char(184) << "Player 1" << endl;

    //Board
    for(int i = 0; i < 10; i++){
        if(i < 9){
            cout << i + 1 << ' ';
        }
        else{
            cout << i + 1;
        }
        for(int j = 0; j < 10; j++){
            if(board[i][j].isOccupied){
                if(board[i][j].player){
                    if(board[i][j].kinged){
                        cout << char(179) << char(232);
                    }
                    else{
                        cout << char(179) << char(176);
                    }
                }
                else{
                    if(board[i][j].kinged){
                        cout << char(179) << char(234);
                    }
                    else{
                        cout << char(179) << char(178);
                    }
                }
            }
            else{
                cout << char(179) << ' ';
            }
        }
        if(i < 9){
            cout << char(179) << endl << "  " << char(195);
            for(int k = 0; k < 19; k++){
                if(k % 2 != 0){
                    cout << char(197);
                }
                else{
                    cout << char(196);
                }
            }
            cout << char(180) << endl;
        }
        else{
            //Bottom edge
            cout << char(179) << endl;
            cout << "  " << char(212);
            for(int k = 0; k < 19; k++){
                if(k % 2 != 0){
                    cout << char(207);
                }
                else{
                    cout << char(205);
                }
            }
            cout << char(190) << "Player 2" << endl;
        }
    }
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
}

bool validateMove(square board[10][10], PlayerMove playerMove, bool playerTurn, bool firstMove){
    //Expect four int values.
    if(playerMove.r1 == 0 and playerMove.c1 == 0 and playerMove.r2 == 0 and playerMove.c2 == 0){
        return true;
    }
    //Verify all numbers are less than or equal to 10 and greater than zero
    if(playerMove.r1 <= 0 or playerMove.c1 <= 0 or playerMove.r2 <= 0 or playerMove.c2 <= 0 or playerMove.r1 > 10 or playerMove.c1 > 10 or playerMove.r2 > 10 or playerMove.c2 > 10){
        return false;
    }
    //Decrement each value for use with board array
    playerMove.r1 --;
    playerMove.c1 --;
    playerMove.r2 --;
    playerMove.c2 --;
    //Check if source is empty
    if(!(board[playerMove.r1][playerMove.c1].isOccupied)){
        cout << "There is no piece to move.\n";
        return false;
    }
    //Check if source is owned by player
    if(board[playerMove.r1][playerMove.c1].player != playerTurn){
        cout << "It's not your turn!\n";
        return false;
    }
    //Check if destination is empty
    if(board[playerMove.r2][playerMove.c2].isOccupied){
        cout << "You can only move to an empty square\n";
        return false;
    }
    //Check diagonal movement
    if(!(abs(playerMove.r2-playerMove.r1) == abs(playerMove.c2-playerMove.c1))){
        cout << "Pieces can only move diagonally.\n";
        return false;
    }
    if(board[playerMove.r1][playerMove.c1].kinged){
        //TODO: Check only one (or none) piece was jumped
    }
    else{
        //Check direction based on player
        if(playerTurn){
            if(!(abs(playerMove.c2-playerMove.c1) == 2) && playerMove.r2 >= playerMove.r1){ //Correct player turn was verified earlier
                cout << "Normal pieces can only move forward.\n";
                return false;
            }
        }
        else{
           if(!(abs(playerMove.c2-playerMove.c1) == 2) && playerMove.r2 <= playerMove.r1){ //Correct player turn was verified earlier
                cout << "Normal pieces can only move forward.\n";
                return false;
            }
        }
        //Check if a piece was jumped
        if(abs(playerMove.c2-playerMove.c1) == 2 && !board[(playerMove.r1+playerMove.r2)/2][(playerMove.c1+playerMove.c2)/2].isOccupied){
            cout << "You can only move one square unless jumping an opponent's piece.\n";
            return false;
        }
        if(!firstMove && abs(playerMove.c2-playerMove.c1) != 2){
            cout << "Consecutive moves can only be made if you are jumping pieces.\n";
            return false;
        }
        //Check for only one square movement
        if(abs(playerMove.c2-playerMove.c1) != 1 && abs(playerMove.c2-playerMove.c1) != 2){
             cout << "You can only move one square at a time unless jumping an opponent's piece.\n";
             return false;
        }
    }
    return true;
}

bool makeMove(square board[10][10], PlayerMove playerMove, bool playerTurn){
    //Check for next turn
    if(playerMove.r1 == 0 and playerMove.c1 == 0 and playerMove.r2 == 0 and playerMove.c2 == 0){
        return true;
    }
    //Decrement each value for use with board array
    playerMove.r1 --;
    playerMove.c1 --;
    playerMove.r2 --;
    playerMove.c2 --;
    //TODO: if king made the move, find the jumped piece
    //else if instead of if
    //if regular jump
    if(abs(playerMove.c2-playerMove.c1) == 2){
        //remove jumped piece
        board[(playerMove.r1+playerMove.r2)/2][(playerMove.c1+playerMove.c2)/2].isOccupied = false;
    }
    //move original piece
    board[playerMove.r2][playerMove.c2].isOccupied = board[playerMove.r1][playerMove.c1].isOccupied;
    board[playerMove.r2][playerMove.c2].kinged = board[playerMove.r1][playerMove.c1].kinged;
    board[playerMove.r2][playerMove.c2].player = board[playerMove.r1][playerMove.c1].player;
    //remove original piece
    board[playerMove.r1][playerMove.c1].isOccupied = false;
    //King if necessary
    if((playerTurn and playerMove.r1 == 9) or playerMove.r1 == 0){
        board[playerMove.r2][playerMove.c2].kinged = true;
    }
    if(abs(playerMove.c2-playerMove.c1) != 2){
        return false;
    }
    return true;
}
PlayerMove getMove(bool firstMove, PlayerMove playerMove, bool playerTurn){
    if(firstMove){
        cout << "Player " << playerTurn + 1 << ": Enter a move in the format [row] [col] [row] [col], example: 1 2 2 3" << endl;
        cin >> playerMove.r1 >> playerMove.c1 >> playerMove.r2 >> playerMove.c2;
    }
    else{
        cout << "Enter another destination square [row] [col] or enter 0 0 to pass";
        cin >> playerMove.r2 >> playerMove.c2;
        if(playerMove.r2 == 0){
            playerMove.r1 = 0;
            playerMove.c1 = 0;
            playerMove.c2 = 0;
        }
    }
    return playerMove;
}

bool checkForWin(square board[10][10]){
    bool player1win = true;
    bool player2win = true;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(board[i][j].isOccupied){
                if(board[i][j].player == false){
                    player1win = false;
                }
                else{
                    player2win = false;
                }
            }
        }
    }
    return !(player1win or player2win);
}

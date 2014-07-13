#include <iostream>
#include <cstdlib>
using namespace std;

struct square{
    bool isOccupied;
    char player;
};

void displayBoard(square board[10][10]);
void checkers(){
    square board[10][10];
    square even;
    square odd;
    even.isOccupied = false;
    even.player = 0;
    odd.isOccupied = true;
    odd.player = 0;

    //initialize board
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(i % 2 == 0){
                if(j % 2 == 0){
                    board[i][j] = even;
                }
                else{
                    board[i][j] = odd;
                }
            }
            else{
                if(j % 2 == 0){
                    board[i][j] = odd;
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
    while(executing){
        bool player = false;
        //moveCommand playerMove; //Make this a struct
        displayBoard(board);
        //while (!validateMove(playerMove)){
            //playerMove = getMove(player);
        //}
        //makeMove(playerMove);


        executing = false;
    }
}

void displayBoard(square board[10][10]){
//display board
    //clear screen
    std::system("cls");
    for(int i = 0; i < 45; i++){
        cout << endl;
    }
    //Top edge
    cout << endl << char(213);
        for(int k = 0; k < 19; k++){
            if(k % 2 != 0){
                cout << char(209);
            }
            else{
                cout << char(205);
            }
        }
    cout << char(184) << endl;

    //Board
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(((i < 4) || (i > 5)) && board[i][j].isOccupied){
                if(board[i][j].player){
                    cout << char(179) << char(176);
                }
                else{
                    cout << char(179) << char(178);
                }
            }
            else{
                cout << char(179) << ' ';
            }
        }
        if(i < 9){
            cout << char(179) << endl << char(195);
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
            cout << char(212);
            for(int k = 0; k < 19; k++){
                if(k % 2 != 0){
                    cout << char(207);
                }
                else{
                    cout << char(205);
                }
            }
            cout << char(190) << endl;
        }
    }
}

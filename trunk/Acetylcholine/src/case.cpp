#include <iostream>
using namespace std;

void printhello(){
    int x = 0;

    cout << "Enter 0 or 1 for hello or goodbye: ";
    cin >> x;

    switch(x){
        case 0:
            cout << "Hello, world!" << endl;
            break;
        case 1:
            cout << "Goodbye, world..." << endl;
            break;
        default:
            cout << "What a moop" << endl;
            break;
    }
}

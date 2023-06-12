#include "GameManager.h"


Game::Game(Board *board) {
    this->player1.setBoard(board);
    this->player2.setBoard(board);
    this->comP.setBoard(board);
    this->board = board;

    cout << "Welcome to Rocket Game !" << endl;
    cout << "Enter sz of Grid: " << endl;
    int sz;
    cin >> sz;
    board->setSize(sz);
    board->intialize(sz);

    cout << "Player 1 choose Rocket A or M: " << endl;
    char rocket;
    cin >> rocket;
    player1.setRocket(rocket);
    player2.setRocket(rocket == 'A' ? 'M' : 'A');
    comP.setRocket(player2.getRocket());
}

bool Game::checkWinner(char rocket) {
    int sz = board->getSize();
    if (rocket == 'A') {
        for (int i = 1; i < sz - 1; ++i) {
            if (board->getBoard(sz - 1, i) != rocket) return false;
        }
        return true;
    } else {
        for (int i = 1; i < sz - 1; ++i) {
            if (board->getBoard(i, sz - 1) != rocket) return false;
        }
        return true;
    }
}


void Game::run() {

    while (true) {
        board->display();

        int oldX, oldY;

        bool err = false;
        do {
            err = false;
            if(!player1.availableMoves()){
                cout << "NO Valid MOVES for Player 1 ... Skip" << endl;
                break;
            }
            cout << "Player 1 turn" << endl;
            cout << "Choose Rocket at pos {x,y} to move: ";
            cin >> oldX >> oldY;
            oldX--;
            oldY--;
            if (!player1.checkValidMove(oldX, oldY)) {
                cout << "\nInvalid Input !" << endl;
                err = true;
            }

        } while (err || !player1.setMove(oldX, oldY, false).first);

        if (checkWinner(player1.getRocket())) {
            cout << "Player 1 Wins !" << endl;
            board->display();
            break;
        }
        //board->display();
        if(comP.availableMoves()) {
            pair<int, int> move = comP.FindBestMove(board, player1);
            oldX = move.first;
            oldY = move.second;
            if (oldX == -1 && oldY == -1) {
                cout << "Player Wins, Congratualtion beat the Comptuer" << endl;
                break;
            } else {
                comP.setMove(oldX, oldY, true);
            }
        }
        else{
            cout << "NO Valid MOVES for Computer ... Skip" << endl;
        }
        if (checkWinner(comP.getRocket())) {
            cout << "Computer Wins !" << endl;
            board->display();
            break;
        }
//        do{
//            err = false;
//            cout << "Player 2 turn" << endl;
//            cout << "Choose Rocket at pos {x,y} to move: ";
//            cin >> oldX >> oldY;
//            oldX--; oldY--;
//            if(!player2.checkValidMove(oldX, oldY)){
//                cout << "\nInvalid Input !" << endl;
//                err = true;
//            }
//        }while(err || !player2.setMove(oldX, oldY,false).first);
//


    }
}
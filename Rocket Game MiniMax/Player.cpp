#include "Player.h"


void Player::setBoard(Board *board) {
    this->board = board;
}

void Player::setRocket(char rocket) {
    this->rocket = rocket;
}

char Player::getRocket() {
    return this->rocket;
}

pair<bool, pair<int, int>> Player::setMove(int oldX, int oldY, bool isComputer) {
    int newY = oldY, newX = oldX;
    if (board->getBoard(oldX, oldY) == this->rocket) {
        if (this->rocket == 'A') {
            if (board->getBoard(oldX + 1, oldY) == 'M') {
                if (board->getBoard(oldX + 2, oldY) == 'M') {
                    if (!isComputer)
                        cout << "Can't move\n";
                    return {false, {-1, -1}};
                }
                newX = oldX + 2;
            } else {
                newX = oldX + 1;
            }
        } else {
            if (board->getBoard(oldX, oldY + 1) == 'A') {
                if (board->getBoard(oldX, oldY + 2) == 'A') {
                    if (!isComputer)
                        cout << "Can't move\n";
                    return {false, {-1, -1}};
                }
                newY = oldY + 2;
            } else {
                newY = oldY + 1;
            }
        }
        board->setBoard(rocket, newX, newY);
        board->setBoard('-', oldX, oldY);
        return {true, {newX, newY}};
    }
    if (!isComputer)
        cout << "Not Empty Place Can't Move" << endl;
    return {false, {-1, -1}};
}

bool Player::checkValidMove(int oldX, int oldY) {
    return (rocket == board->getBoard(oldX, oldY) && (oldX < board->getSize() - 1) && (oldY < board->getSize() - 1));
}

bool Player::availableMoves() {

    if(this->rocket == 'A'){
        for(int i = 0; i < board->getSize()-1; ++i){
            for(int j = 0; j < board->getSize()-1; ++j){
                if(board->getBoard(i,j) == 'A'){
                    if(board->getBoard(i+1,j) == 'M' && board->getBoard(i+2,j) == 'M'){
                        continue;
                    }
                    return true;
                }
            }
        }
    }
    else{
        for(int i = 0; i < board->getSize()-1; ++i){
            for(int j = 0; j < board->getSize()-1; ++j){
                if(board->getBoard(i,j) == 'M'){
                    if(board->getBoard(i,j+1) == 'A' && board->getBoard(i,j+2) == 'A'){
                        continue;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

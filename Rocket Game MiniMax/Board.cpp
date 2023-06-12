#include "Board.h"

Board::Board(int sz) {
    this->size = sz;
}

int Board::getSize() const {
    return size;
}

void Board::setSize(int sz) {
    this->size = sz;
}


void Board::intialize(int sz) {
    grid.resize(sz, vector<char>(sz));

    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            grid[i][j] = '-';
        }
    }
    for (int j = 1; j < sz - 1; ++j) {
        grid[0][j] = 'A';
        grid[j][0] = 'M';
    }
}

char Board::getBoard(int x, int y) {
    return grid[x][y];
}

void Board::setBoard(char rocket, int x, int y) {

    grid[x][y] = rocket;
}

void Board::display() {
    for (int i = 0; i < size; ++i) {
        if (i == 0) {
            for (int j = 0; j < size; ++j) {
                cout << setw(7) << left << setw(3) << " " << j + 1 << setw(4) << " ";
            }
            cout << endl;
        }
        for (int j = 0; j < size; ++j) {
            if (j == 0) {
                cout << i + 1 << setw(2) << " ";
            }
            cout << setw(5) << left << grid[i][j] << setw(3) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<char>> Board::getGrid() {
    return this->grid;
}
#pragma once

#include <bits/stdc++.h>

using namespace std;

class Board {
private :
    int size;
    vector<vector<char>> grid;
public :
    Board() = default;

    explicit Board(int sz);

    void setSize(int sz);

    void intialize(int sz);

    char getBoard(int x, int y);

    vector<vector<char>> getGrid();

    int getSize() const;

    void setBoard(char rocket, int x, int y);

    void display();
};
#pragma once
#include <bits/stdc++.h>
#include "Board.h"
using namespace std;


class Player {
protected:
    char rocket;
    Board *board;
public:
    Player() = default;

    void setBoard(Board *board);

    void setRocket(char rocket);

    pair<bool, pair<int, int>> setMove(int oldX, int oldY, bool isComputer);

    Board *getBoard();

    bool checkValidMove(int oldX, int oldY);

    bool availableMoves();
    char getRocket();
};

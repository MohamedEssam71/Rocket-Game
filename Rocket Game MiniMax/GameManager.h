#pragma once
#include <bits/stdc++.h>
#include "Board.h"
#include "Player.h"
#include "ComputerPlayer.h"
using namespace std;

class Game {
public :

private:

    Player player1;
    Player player2;
    ComputerPlayer comP;
    Board *board;

public:
    Game(Board *board);

    void run();

    bool checkWinner(char rocket);

};
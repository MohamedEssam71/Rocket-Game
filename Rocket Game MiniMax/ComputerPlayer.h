#pragma once
#include <bits/stdc++.h>
#include "Player.h"
using namespace std;


class ComputerPlayer : public Player {
public:
    int miniMax(Board *board, Player p1, int depth, bool isMax);

    pair<int, int> FindBestMove(Board *board, Player p1);

    bool checkWinner(char rocket);

};
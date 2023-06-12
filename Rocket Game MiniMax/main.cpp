#include <bits/stdc++.h>
#include "GameManager.h"
using namespace std;


int main() {
    Board *board = new Board();
    Game game(board);
    game.run();
    system("pause");
}

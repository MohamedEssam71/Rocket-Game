#include "ComputerPlayer.h"


bool ComputerPlayer::checkWinner(char rocket) {
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

int ComputerPlayer::miniMax(Board *board, Player p1, int depth, bool isMax) {
    char compRocket = this->rocket;
    char playerRocket = p1.getRocket();

    if (checkWinner(compRocket)) {
        return 1e9 - depth;
    }
    else if (checkWinner(playerRocket)) {
        return -1e9 + depth;
    }
    else {
        if (isMax) {
            int best = -1e9;
            for (int i = 0; i < board->getSize() - 1; ++i) {
                for (int j = 0; j < board->getSize() - 1; ++j) {
                    if (board->getBoard(i, j) == compRocket) {
                        if (checkValidMove(i, j)) {
                            pair<int, int> mov = setMove(i, j, true).second;
                            if (mov.first == -1 || mov.second == -1) continue;

                            board->setBoard(compRocket, mov.first, mov.second);
                            board->setBoard('-', i, j);

                            best = max(best, miniMax(board, p1, depth + 1, !isMax));

                            board->setBoard(compRocket, i, j);
                            board->setBoard('-', mov.first, mov.second);


                        } else {
                            continue;
                        }
                    }
                }
            }
            return best;
        } else {
            int best = 1e9;
            for (int i = 0; i < board->getSize() - 1; ++i) {
                for (int j = 0; j < board->getSize() - 1; ++j) {
                    if (board->getBoard(i, j) == playerRocket) {
                        if (p1.checkValidMove(i, j)) {
                            pair<int, int> mov = p1.setMove(i, j, true).second;
                            if (mov.first == -1 || mov.second == -1) continue;
//
                            board->setBoard(playerRocket, mov.first, mov.second);
                            board->setBoard('-', i, j);

                            best = min(best, miniMax(board, p1, depth + 1, !isMax));

                            board->setBoard(playerRocket, i, j);
                            board->setBoard('-', mov.first, mov.second);

                        } else {
                            continue;
                        }
                    }
                }
            }
            return best;
        }
    }
}

pair<int, int> ComputerPlayer::FindBestMove(Board *board, Player p1) {
    pair<int, int> bestMove = {-1, -1};
    int bestValue = INT_MIN;
    char compRocket = this->rocket;
    for (int i = 0; i < board->getSize() - 1; ++i) {
        for (int j = 0; j < board->getSize() - 1; ++j) {
            if (board->getBoard(i, j) == compRocket) {
                if (checkValidMove(i, j)) {
                    pair<int, int> mov = setMove(i, j, true).second;
                    if (mov.first == -1 || mov.second == -1) continue;

                    board->setBoard(compRocket, mov.first, mov.second);
                    board->setBoard('-', i, j);

                    int movValue = miniMax(board, p1, 0, false);

                    board->setBoard(compRocket, i, j);
                    board->setBoard('-', mov.first, mov.second);

                    if (movValue > bestValue) {
                        bestValue = movValue;
                        bestMove = {i, j};
                    }
                }
            }
        }
    }
    return bestMove;
}
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

    int getSize() const;

    void setBoard(char rocket, int x, int y);

    void display();
};


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


class Player {
protected:
    char rocket;
    Board *board;
public:
    Player() = default;

    ~Player() {
        board = nullptr;
        delete board;
    };

    void setBoard(Board *board);

    void setRocket(char rocket);

    bool setMove(int oldX, int oldY, bool isComputer);

    Board *getBoard();

    char getRocket();

    bool checkValidMove(char rocket);
};

void Player::setBoard(Board *board) {
    this->board = board;
}

void Player::setRocket(char rocket) {
    this->rocket = rocket;
}

char Player::getRocket() {
    return this->rocket;
}

bool Player::setMove(int oldX, int oldY, bool isComputer) {
    int newY = oldY, newX = oldX;
    if (board->getBoard(oldX, oldY) == this->rocket) {
        if (this->rocket == 'A') {
            if (board->getBoard(oldX + 1, oldY) == 'M') {
                if (board->getBoard(oldX + 2, oldY) == 'M') {
                    if (!isComputer)
                        cout << "Can't move\n";
                    return false;
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
                    return false;
                }
                newY = oldY + 2;
            } else {
                newY = oldY + 1;
            }
        }
        board->setBoard(rocket, newX, newY);
        board->setBoard('-', oldX, oldY);
        return true;
    }
    if (!isComputer)
        cout << "Not Empty Place Can't Move" << endl;
    return false;
}

bool Player::checkValidMove(char rocket) {
    if (rocket == 'A') {
        for (int i = 0; i < board->getSize() - 1; ++i) {
            for (int j = 0; j < board->getSize() - 1; ++j) {
                if (board->getBoard(i, j) == 'A') {
                    if (board->getBoard(i + 1, j) == '-') return true;
                    if (board->getBoard(i + 1, j) == 'M' && board->getBoard(i + 2, j) == '-')
                        return true;
                }
            }
        }
    } else {
        for (int i = 0; i < board->getSize() - 1; ++i) {
            for (int j = 0; j < board->getSize() - 1; ++j) {
                if (board->getBoard(i, j) == 'M') {
                    if (board->getBoard(i, j + 1) == '-') return true;
                    if (board->getBoard(i, j + 1) == 'A' && board->getBoard(i, j + 2) == '-')
                        return true;
                }
            }
        }
    }
    return false;
}

class ComputerPlayer {
public:
    int generateMove(Player p2, Player p1, Board boardCopy, bool turns, int alpha, int beta);
};

int ComputerPlayer::generateMove(Player p2, Player p1, Board boardCopy, bool turns, int alpha, int beta) {
    Board boardNew = boardCopy;
    Player currentPlayer;
    int temp;
    if (turns) {
        currentPlayer = p2;
        temp = -1e9;
    } else {
        currentPlayer = p1;
        temp = 1e9;
    }
    currentPlayer.setBoard(&boardNew);

    for (int i = 1; i < boardNew.getSize() - 1; ++i) {
        boardNew = boardCopy;
        currentPlayer.setBoard(&boardNew);

        int oldX = -1, oldY = -1;
        if (!currentPlayer.checkValidMove(currentPlayer.getRocket())) {
            return generateMove(p2, p1, boardNew, !turns, alpha, beta);
        }
        if (currentPlayer.getRocket() == 'A') {

            oldY = i;
            for (int j = 0; j < boardCopy.getSize() - 1; ++j) {
                if (boardCopy.getBoard(j, oldY) == currentPlayer.getRocket()) {
                    oldX = j;
                }
            }
        } else {
            oldX = i;
            for (int j = 0; j < boardCopy.getSize() - 1; ++j) {
                if (boardCopy.getBoard(oldX, j) == currentPlayer.getRocket()) {
                    oldY = j;
                }
            }
        }
        if (oldX == -1 || oldY == -1) {
            continue;
        }
        if (!currentPlayer.setMove(oldX, oldY, true)) {
            continue;
        }
        bool isWinner = true;
        if (currentPlayer.getRocket() == 'A') {
            for (int i = 1; i < boardNew.getSize() - 1; ++i) {
                if (boardNew.getBoard(boardNew.getSize() - 1, i) != currentPlayer.getRocket()) {
                    isWinner = false;
                }
            }
        } else {
            for (int i = 1; i < boardNew.getSize() - 1; ++i) {
                if (boardNew.getBoard(i, boardNew.getSize() - 1) != currentPlayer.getRocket()) {
                    isWinner = false;
                }
            }
        }
        if (isWinner) {
            if (turns)
                return 1;
            else
                return -1;
        }
        if (turns) {
            temp = max(generateMove(p2, p1, boardNew, !turns, alpha, beta), temp);
            alpha = max(temp, alpha);
        } else {
            temp = min(generateMove(p2, p1, boardNew, !turns, alpha, beta), temp);
            beta = min(temp, beta);
        }
        if (beta <= alpha) {
            return temp;
        }
    }
    return temp;
}


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

Game::Game(Board *board) {
    this->player1.setBoard(board);
    this->player2.setBoard(board);

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
    vector<int> rates(board->getSize(), -1e9);
    while (true) {
        board->display();

        int oldX, oldY;
        do {
            if (!player1.checkValidMove(player1.getRocket())) {
                cerr << "No Valid Moves for Player 1" << endl;
                break;
            }
            cout << "Player 1 turn" << endl;
            cout << "Choose Rocket pos to move: ";
            if (player1.getRocket() == 'A') {
                cin >> oldY;
                oldY--;
                for (int i = 0; i < board->getSize() - 1; ++i) {
                    if (board->getBoard(i, oldY) == player1.getRocket()) {
                        oldX = i;
                    }
                }
            } else {
                cin >> oldX;
                oldX--;
                for (int i = 0; i < board->getSize() - 1; ++i) {
                    if (board->getBoard(oldX, i) == player1.getRocket()) {
                        oldY = i;
                    }
                }
            }

        } while (!player1.setMove(oldX, oldY, false));

        if (checkWinner(player1.getRocket())) {
            cout << "Player 1 Wins !" << endl;
            board->display();
            break;
        }
        board->display();

        Board boardNew = *board;
        bool turns = true;
        for (int i = 1; i < boardNew.getSize() - 1; ++i) {
            boardNew = *board;
            player2.setBoard(&boardNew);

            int oldX, oldY;
            if (!player2.checkValidMove(player2.getRocket())) {
                break;
            }
            if (player2.getRocket() == 'A') {

                oldY = i;
                for (int j = 0; j < boardNew.getSize() - 1; ++j) {
                    if (boardNew.getBoard(j, oldY) == player2.getRocket()) {
                        oldX = j;
                    }
                }
            } else {
                oldX = i;
                for (int j = 0; j < boardNew.getSize() - 1; ++j) {
                    if (boardNew.getBoard(oldX, j) == player2.getRocket()) {
                        oldY = j;
                    }
                }
            }
            if (!player2.setMove(oldX, oldY, true)) {
                continue;
            }

            rates[i] = comP.generateMove(player2, player1, boardNew, !turns, -1, 1);
        }
        player2.setBoard(board);

        int maxRate = -1e9;
        for (auto pair: rates) {
            maxRate = max(pair, maxRate);
        }
        for (int i = 0; i < rates.size(); ++i) {
            if (maxRate == rates[i]) {
                if (player2.getRocket() == 'A') {
                    oldY = i;
                    if (oldY >= board->getSize()) oldY = board->getSize() - 1;
                    for (int j = 0; j < board->getSize() - 1; ++j) {
                        if (board->getBoard(j, oldY) == player2.getRocket()) {
                            oldX = j;
                        }
                    }
                } else {
                    oldX = i;
                    if (oldX >= board->getSize()) oldX = board->getSize() - 1;
                    for (int j = 0; j < board->getSize() - 1; ++j) {
                        if (board->getBoard(oldX, j) == player2.getRocket()) {
                            oldY = j;
                        }
                    }
                }
                player2.setMove(oldX, oldY, true);
                break;
            }
        }
        rates = vector<int>(board->getSize(), -1e9);

        if (checkWinner(player2.getRocket())) {
            cout << "Player 2 Wins !" << endl;
            board->display();
            break;
        }

    }
}


int main() {
    Board *board = new Board();
    Game game(board);
    game.run();
    system("pause");
}

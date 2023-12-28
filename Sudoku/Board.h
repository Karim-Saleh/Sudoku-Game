#include "Cell.h"
#include "Position.h"
#include <string>
using namespace std;
class Board
{
private:
    Cell unsolved[10][10], solved[10][10];
    Position solverPos;
    int hints, validations, initialCount;

public:
    Board();
    void gameLoading();
    bool solver();
    bool checkRow(Position test, int value);
    bool checkColumn(Position test, int value);
    bool checkBox(Position test, int value);
    bool isOkay(Position test, int value);
    void incrementPos();
    void decrementPos();
    void levelBuild(string level);
    bool validation(bool program);
    void hint();
    void setValue(Position position, int value);
    void print();
    int getValue(Position position);
    void restartGame();
    bool availableCell(Position position);
    bool fullBoard();
    Position* storeAvailableCells(int& count);
};
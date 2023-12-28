#include "Position.h"

Position::Position()
{
    row = 0;
    column = 0;
}

Position::Position(int row, int column)
{
    Position::row = row;
    Position::column = column;
}

void Position::setRow(int row)
{
    Position::row = row;
}
void Position::setColumn(int column) {
    Position::column = column;
}
int Position::getRow() {
    return row;
}
int Position::getColumn() {
    return column;
}

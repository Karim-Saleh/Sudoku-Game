#pragma once
class Position
{
private:
	int row, column;

public:
	Position();
	Position(int row, int column);

	int getRow();
	int getColumn();

	void setRow(int row);
	void setColumn(int column);
};

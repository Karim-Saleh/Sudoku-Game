#pragma once
#include "Position.h"
class Step
{
private:
	Position position;
	int oldValue, newValue;

public:
	Step();
	void setPosition(Position position);
	void setOldValue(int old);
	void setNewValue(int New);

	Position getPosition();
	int getOldValue();
	int getNewValue();
};
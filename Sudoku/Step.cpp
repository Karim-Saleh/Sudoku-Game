#include "Step.h"
#include "Position.h"

Step::Step()
{
	oldValue = 0;
	newValue = 0;
}

void Step::setPosition(Position position)
{
	Step::position = position;
}

void Step::setOldValue(int old)
{
	oldValue = old;
}

void Step::setNewValue(int New)
{
	newValue = New;
}

Position Step::getPosition()
{
	return position;
}

int Step::getOldValue()
{
	return oldValue;
}

int Step::getNewValue()
{
	return newValue;
}
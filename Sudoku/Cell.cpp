#include "Cell.h"

void Cell::setValue(int value)
{
	Cell::value = value;
}

void Cell::setInitial(bool first)
{
	Cell::initial = first;
}

void Cell::setChangable(bool changable)
{
	Cell::changable = changable;
}

int Cell::getValue()
{
	return value;
}

bool Cell::isInitial()
{
	return initial;
}

bool Cell::isChangable()
{
	return changable;
}
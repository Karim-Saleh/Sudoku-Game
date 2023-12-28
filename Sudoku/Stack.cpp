#include "Stack.h"
#include "Step.h"
#include<iostream>
Stack::Stack() {
	elements = 0;
	capacity = 10;
	Arr = new Step[capacity];
}
void Stack::push(Step step) {
	if (capacity == elements) {
		expand();
	}
	Arr[elements] = step;
	elements++;
}
Step Stack::pop() {
	if (!isEmpty()) {
		elements--;
		Step value = Arr[elements];
		return value;
	}
	else
	{
		Step step; //here row, column, oldValue, newValue equal zero
		return step;
	}
}
void Stack::expand() {
	Step* newarray = new Step[capacity * 2];
	for (int i = 0; i < capacity; i++) {

		newarray[i] = Arr[i];
	}
	capacity *= 2;
	delete Arr;
	Arr = newarray;

}
bool Stack::isEmpty()
{
	return(elements == 0);
}

void Stack::delstack()
{
	elements = 0;
	capacity = 10;
	delete[]Arr;
	Arr = new Step[capacity];
}

Step Stack::RecallStep()
{
	Step lastStep = Arr[elements];
	push(lastStep);
	return lastStep;
}

Stack::~Stack() {
	delete[]Arr;
}
#include "Step.h"
class Stack
{
private:
	Step* Arr;
	int elements;
	int capacity;

public:
	Stack(void);
	void push(Step step);
	Step pop();
	Step RecallStep();
	void expand();
	bool isEmpty();
	void delstack();
	~Stack(void);
};
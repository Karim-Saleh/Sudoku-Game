#include <iostream>
#include <string>
#include "Board.h"
#include "Step.h"
#include "Position.h"
#include "Stack.h"
#include <chrono>
#include <cmath>

using namespace std;

Board board;
Stack history;
string input;
Position position;
int takenSec, sec, Min, hours, undoCounter = 0, steps = 0;
auto start = chrono::system_clock::now();

bool validInteger();
int toInt();
bool charFn();
bool play();
void calcTime();
bool determineLevel();
void undo();
void redo();

int main()
{
    cout << " Welcome to Sudoku Game\n";
    determineLevel();
    start = chrono::system_clock::now();
    while (1)
    {
        board.print();
        if (!(charFn() || play()))
        {
            cout << " WRONG INPUT !!!\n You must follow game's instructions\n";
            cout << " Please enter any key to continue\n ";
            getline(cin, input);
        }
        if (board.fullBoard())
        {

            if (board.validation(true))
            {
                //won
                //high score : input name;
                auto end = chrono::system_clock::now();
                takenSec = round(chrono::duration <double, milli>(end - start).count() / 1000);
                break;
            }
            else
            {
                //lose
            }
        }
    }
    cout << " You took time of ";
    calcTime();
    cout << ", and made " << steps << " steps.";
    return 0;
}

bool determineLevel()
{
    cout << " Choose game Difficulty:\n";
    cout << " 1-Easy.\n 2-Medium.\n 3-Hard.\n ";
    cin >> input;
    cin.ignore();
    if (!(input == "1" || input == "2" || input == "3"))
    {
        system("cls");
        cout << " INVALID INPUT !!!\n";
        return determineLevel();
    }
    else
    {
        board.levelBuild(input);
        return true;
    }
}

bool validInteger() //Returns true if input is between (1 : 9)
{
    return (input.length() == 1) && (input[0] >= 49 && input[0] <= 57);
}

int toInt() //Converts a charachter to integer
{
    int value = input[0] - 48;
    return value;
}

bool charFn() //Returns true if input is a charachter (v, V, u, U, h, H, r, R) and calls its function
{
    cout << " ";
    cin >> input;
    cin.ignore();
    if (input.length() != 1)
        return false;
    switch (input[0])
    {
    case 'u':
    case 'U':
        undo();
        break;
    case 'r':
    case 'R':
        redo();
        break;
    case 'h':
    case 'H':
        board.hint();
        break;
    case 'v':
    case 'V':
        board.validation(false);
        break;
    case 's':
    case 'S':
        board.restartGame();
        history.delstack();
        start = chrono::system_clock::now();//test
        steps = 0;
        undoCounter = 0;
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool play() //Returns true if all input position values and cell value are valid numbers and set it into the board
{
    if (validInteger())
    {
        position.setRow(toInt());
        cout << " ";
        cin >> input;
        cin.ignore();
    }
    else
        return false;
    if (validInteger())
    {
        position.setColumn(toInt());
        if (!board.availableCell(position))
        {
            cout << " You can not change this cell\n";
            cout << " Please enter any key to continue\n ";
            getline(cin, input);
            return true;
        }
        cout << " ";
        cin >> input;
        cin.ignore();
    }
    else
        return false;
    if (validInteger())
    {
        //Setting value to the entered position and store this step into history
        Step step;
        int value;
        value = toInt();
        step.setPosition(position);
        step.setOldValue(board.getValue(position));
        board.setValue(position, value);
        step.setNewValue(value);
        history.push(step);
        undoCounter = 0;
        steps++;
        return true;
    }
    else
        return false;
} //Good job

void undo() 
{
    if (history.isEmpty())
    {
        cout << " You must make at least one step to undo.\n";
    }
    else
    {
        bool unavailable = true;
        while (!history.isEmpty()) //avoid undo a value after it became valid
        {
           Step step = history.pop();
           if (board.availableCell(step.getPosition()))
           {
               board.setValue(step.getPosition(), step.getOldValue());
               undoCounter++;
               cout << " Done.\n";
               unavailable = false;
               break;
           }
        }
        if (unavailable) //If all values in stack are valid
        {
            cout << " Your last step(s) is/are valid and you can't undo it/them.\n";
        }
    }
    cout << " Please enter any key to continue.\n ";
    getline(cin, input);
}

void redo()
{
    if (undoCounter > 0)
    {
        Step restep = history.RecallStep();
        board.setValue(restep.getPosition(), restep.getNewValue());
        cout << " Done.\n";
        undoCounter--;
    }
    else
    {
        cout << " You must undo first.\n";
    }
    cout << " Please enter any key to continue.\n ";
    getline(cin, input);
}

void calcTime() //Calculates time like hh:mm:ss
{
    //Calculating
    Min = takenSec / 60;
    sec = takenSec % 60;
    hours = Min / 60;
    Min = Min % 60;

    //Printing
    if (hours / 10 < 1)
    {
        cout << 0 << hours << ":";
    }
    else
    {
        cout << hours << ":";
    }
    if (Min / 10 < 1)
    {
        cout << 0 << Min << ":";
    }
    else
    {
        cout << Min << ":";
    }
    if (takenSec / 10 < 1)
    {
        cout << 0 << sec;
    }
    else
    {
        cout << sec;
    }
}
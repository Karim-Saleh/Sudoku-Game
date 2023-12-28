#include "Board.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

Board::Board()
{
    initialCount = 0;
    solverPos.setRow(1);
    solverPos.setColumn(1);
    hints = 5;
    validations = 3;
    gameLoading();
    solver();
}

void Board::gameLoading()
{
    srand(time(NULL));
    stringstream num;
    string file = "Games/Game", temp;
    int randomNum = (rand() % 20) + 1;
    num << randomNum;
    num >> temp;
    file = file +" " + "20" + ".txt";
    ifstream gameFile(file);
    for (int row = 1; row < 10; row++)
    {
        for (int column = 1; column < 10; column++)
        {
            int value;
            gameFile >> value;
            solved[row][column].setValue(value);
            unsolved[row][column].setValue(value);
            if (value != 0)
            {
                solved[row][column].setInitial(true);
                solved[row][column].setChangable(false);
                unsolved[row][column].setInitial(true);
                unsolved[row][column].setChangable(false);
                initialCount++;
            }
        }
    }
    gameFile.close();
}

bool Board::checkRow(Position test, int value)
{
    for (int i = 1; i < 10; i++)
    {

        if (solved[test.getRow()][i].getValue() == value)
        {
            return false;
        }

    }
    return true;
}

bool Board::checkBox(Position test, int value)
{
    int boxRow, boxColumn, row, column;
    boxRow = ((test.getRow() - 1) / 3) + 1;
    boxColumn = ((test.getColumn() - 1) / 3) + 1;
    row = ((boxRow - 1) * 3) + 1;
    column = ((boxColumn - 1) * 3) + 1;
    for (int i = row; i < row + 3; i++)
    {
        for (int j = column; j < column + 3; j++)
        {
            if (solved[i][j].getValue() == value)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::checkColumn(Position test, int value) {
    for (int column = 1; column < 10; column++) {
        if (solved[column][test.getColumn()].getValue() == value)
            return false;
    }

    return true;
}

bool Board::isOkay(Position test, int value)
{
    return checkColumn(test, value) && checkRow(test, value) && checkBox(test, value);
}

void Board::incrementPos()
{
    if (solverPos.getColumn() == 9)
    {
        solverPos.setColumn(1);
        solverPos.setRow(solverPos.getRow() + 1);
    }
    else
    {
        solverPos.setColumn(solverPos.getColumn() + 1);
    }
}

void Board::decrementPos()
{
    if (solverPos.getColumn() == 1)
    {
        solverPos.setColumn(9);
        solverPos.setRow(solverPos.getRow() - 1);
    }
    else
    {
        solverPos.setColumn(solverPos.getColumn() - 1);
    }
}

bool Board::solver()
{
    //The initial values that we musn't change
    if (solved[solverPos.getRow()][solverPos.getColumn()].isInitial())
    {
        //new

        // if we reached the last cell and it has already an initial value then we are done
        if (solverPos.getRow() == 9 && solverPos.getColumn() == 9)
        {
            return true;
        }
        incrementPos(); //incrementing the position to skip this function call

        ///////////

        if (solver()) //Going to the next cell
        {
            return true;
        }
        else
        {
            decrementPos(); //Decrementing the position to go back to the previous cell
            return false;
        }
    }


    for (int value = 1; value < 10; value++)
    {
        if (isOkay(solverPos, value)) //if the value is valid for the current cell
        {
            solved[solverPos.getRow()][solverPos.getColumn()].setValue(value); //assigning the value to the cell
            if (solverPos.getRow() == 9 && solverPos.getColumn() == 9) //if we reached the last cell then we are done
            {
                return true;
            }
            incrementPos(); //Incrementing the position to go to the next cell
            if (solver()) //Going to the next cell
            {
                return true;
            }
        }
    }
    //new

    //assigning 0 to the current cell to avoid constraints inconsistency
    solved[solverPos.getRow()][solverPos.getColumn()].setValue(0);

    ///////
    decrementPos(); //Decrementing the position to go back to the previous cell
    return false;
}

void Board::levelBuild(string level)
{
    int max;
    srand(time(NULL)); //Makes the rand() function generate different values
    
    switch (level[0]) //Determine the number of initial cells based on the user difficulty choice
    {
    case '1': //Easy
        max = 40;
        break;
    case '2': //Medium
        max = 35;
        break;
    default:
        max = 25;
        break;
    }
    while (initialCount < max)
    {
        Position position((rand() % 9) + 1, (rand() % 9) + 1); //Generate random cell Position
        if (!unsolved[position.getRow()][position.getColumn()].isInitial()) //if the current position wasn't generated before
        {
            int value = solved[position.getRow()][position.getColumn()].getValue(); //Taking the generated cell position value

            //Assigning the value
            unsolved[position.getRow()][position.getColumn()].setValue(value);
            unsolved[position.getRow()][position.getColumn()].setInitial(true);
            unsolved[position.getRow()][position.getColumn()].setChangable(false);
            //

            initialCount++;
        }
    }
}

void Board::restartGame()
{
    for (int row = 1; row < 10; row++)
    {
        for (int column = 1; column < 10; column++)
        {
            if (!unsolved[row][column].isInitial())
            {
                unsolved[row][column].setValue(0);
                unsolved[row][column].setChangable(true);
            }

        }
    }
    hints = 5;
    validations = 3;
}

int Board::getValue(Position position)
{
    return unsolved[position.getRow()][position.getColumn()].getValue();
}

void Board::setValue(Position position, int value)
{
    unsolved[position.getRow()][position.getColumn()].setValue(value);
}

void Board::print()
{
    system("cls");
    cout << setw(39) << "1   2   3   4   5   6   7   8   9" 
        << setw(20) << "Instructions" << endl;
    cout << setw(41) << "-------------------------------------" << setw(7);
    for (int i = 1; i < 13; i++) cout << '_';
    cout << endl;

    for (int i = 1; i < 10; i++)
    {
        cout <<setw(2) << i <<setw(4) << "|| ";//row num
        for (int x = 1; x < 10; x++)
        {
            if (unsolved[i][x].getValue() != 0)
                cout << unsolved[i][x].getValue();
            else
                cout << '.';
            if (x == 3 || x == 6)
            {
                cout <<setw(3) << "| ";
            }
            else if (x != 9) {
                cout << setw(4);
            }
            if (x == 9)
            {
                cout << " || ";
                switch (i)
                {
                case 1:
                    cout << setw(13) << "U : Undo.";
                    break;
                case 2:
                    cout << setw(13) << "H : Hint." <<setw(17) <<"[" << hints
                        << " remaining]";
                    break;
                case 3:
                    cout <<setw(21) << "S : Restart Game.";
                    break;
                case 4:
                    cout <<setw(58)
                        << "Note : You can use characters either capital or small.";
                    break;
                }
            }
        }
        cout << endl;
        if (i == 3 || i == 6)
        {
            cout << setw(42) << "||-----------+-----------+-----------||";
            if (i == 3)
                cout << setw(56) << "For playing enter row, column & value respectively.";
             cout << endl;
        }
        else if (i == 9)
        {
            cout << setw(41) << "-------------------------------------" << endl;
        }
        else
        {
            cout << setw(5) << "||" << setw(12) << "|" << setw(12) << "|"
                << setw(13) << "||";
            switch (i)
            {
            case 1:
                cout << setw(14) << "R : Redo.";
                break;
            case 2:
                cout << setw(26) << "V : Check Validation." << setw(5)
                    << "[" << validations << " remaining]";
                break;
            }
            cout << endl;
        }
    }
}

bool Board::availableCell(Position position)
{
    return unsolved[position.getRow()][position.getColumn()].isChangable();
}

bool Board::fullBoard()
{
    for (int row = 1; row < 10; row++)
    {
        for (int column = 1; column < 10; column++)
        {
            if (unsolved[row][column].getValue() == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::validation(bool program)
{
    bool test = true, print = true;
    int valid = 0, invalid = 0;
    if (validations > 0 || program)
    {
        for (int row = 1; row < 10; row++)
        {
            for (int column = 1; column < 10; column++)
            {
                if (unsolved[row][column].isChangable() == 1
                    && unsolved[row][column].getValue() != 0)
                {
                    if (solved[row][column].getValue() == unsolved[row][column].getValue())
                    {
                        unsolved[row][column].setChangable(0);
                        valid++;
                    }
                    else
                    {
                        if (print)
                        {
                            cout << "\n Invalid Values:\n ";
                            for (int i = 1; i < 40; i++)
                                cout << "-";
                            cout << "\n |Cell    |Row    |Column    |Value    |\n ";
                            for (int i = 1; i < 40; i++)
                            {
                                if (i == 10 || i == 18 || i == 29)
                                {
                                    cout << '+';
                                    continue;
                                }
                                cout << '-';
                            }
                            print = false;
                            cout << '\n';
                        }
                        invalid++;
                        cout << " |" << invalid << setw(8) << "|" << row << setw(7) << "|" << column << setw(10) << "|"
                            << unsolved[row][column].getValue() << setw(9) << "|" << endl;
                        test = false;
                    }
                }
            }
        }
        //If all values are vaild
        if (test && valid != 0 && !program)
        {
            cout << " All good.\n";
            cout << " Please enter any key to continue.\n ";
            string input;
            getline(cin, input);
        }
        if (!test)
        {
            cout << " ";
            for (int i = 1; i < 40; i++)
                cout << "-";
            cout << "\n Please enter any key to continue.\n ";
            string input;
            getline(cin, input);
        }
    }
    else
    {
        cout << " Sorry, you don't have validations!\n";
        cout << " Please enter any key to continue.\n ";
        string input;
        getline(cin, input);
    }
    if (!program && (valid != 0 || invalid != 0))
        validations--;
    return test;
}

void Board::hint()
{
    if (hints > 0)
    {
        int count = 0;
        Position* available = storeAvailableCells(count);
        int randIndex = rand() % count;
        int row = available[randIndex].getRow(), column = available[randIndex].getColumn(),
            value = solved[row][column].getValue();
        setValue(available[randIndex], value);
        unsolved[row][column].setChangable(false);
        cout << " Your hint is in\n Row" << setw(8) << row << endl << " Column" 
            <<setw(5) << column << endl << " Value" << setw(6) << value << endl
            << " Please enter any key to continue.\n ";
        string input;
        getline(cin, input);
        hints--;
    }
    else
    {
        cout << " Sorry, you don't have any hints!\n";
        cout << " Please enter any key to continue. \n";
        string input;
        getline(cin, input);
    }
}

Position* Board::storeAvailableCells(int& count)
{
    Position arr[81];
    for (int row = 1; row < 10; row++)
    {
        for (int column = 1; column < 10; column++)
        {
            Position temp(row, column);
            temp.setColumn(column);
            if (availableCell(temp))
            {
                arr[count] = temp;
                count++;
            }
        }
    }
    return arr;
}
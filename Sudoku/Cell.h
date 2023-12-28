class Cell
{
private:
    int value = 0;
    bool initial = 0, changable = 1;

public:
    void setValue(int value);
    void setInitial(bool first);
    void setChangable(bool changable);

    int getValue();
    bool isInitial();
    bool isChangable();
};
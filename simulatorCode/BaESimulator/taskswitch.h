#ifndef TASKSWITCH_H
#define TASKSWITCH_H

class TaskSwitch
{
public:
    TaskSwitch();
    void updateValue(int newVal);
    int getValue();
private:
    int value;
};

#endif // TASKSWITCH_H

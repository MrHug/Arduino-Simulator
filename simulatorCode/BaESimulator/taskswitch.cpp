#include "taskswitch.h"

TaskSwitch::TaskSwitch()
{
    this->value = 0;
}

void TaskSwitch::updateValue(int newVal) {
    this->value = newVal;
}

int TaskSwitch::getValue() {
    return this->value;
}

#include "command.h"

Command::Command(Company* company, Department* department, Employee* employee)
{
    this->company = company;
    this->department = department;
    this->employee = employee;
}

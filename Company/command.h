#ifndef COMMAND_H
#define COMMAND_H
#include "company.h"

class Command
{
public:
    Command(Company* company = nullptr, Department* department = nullptr, Employee* employee = nullptr);
    virtual ~Command() = default;

    virtual void execute() = 0;
    virtual void undo() = 0;

protected:
    Company* company;
    Department* department;
    Employee* employee;
};
#endif

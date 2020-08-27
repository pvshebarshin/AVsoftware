#ifndef COMMANDREMOVEEMPLOYEE_H
#define COMMANDREMOVEEMPLOYEE_H
#include "command.h"
#include "company.h"

class CommandRemoveEmployee : public Command
{
public:
    CommandRemoveEmployee(Company* company, Department* department, Employee* employee);
    void execute() override;
    void undo() override;

private:
    QString departamentName;
    QString name;
    QString surname;
    QString middleName;
    QString function;
    QString id;
    uint32_t salary;
};
#endif

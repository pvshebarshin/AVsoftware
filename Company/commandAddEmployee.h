#ifndef COMMANDADDEMPLOYEE_H
#define COMMANDADDEMPLOYEE_H
#include "command.h"
#include "company.h"

class CommandAddEmployee : public Command
{
public:
    CommandAddEmployee(Company* company, Department* department,QString name,
                       QString surname, QString middleName, QString function , uint32_t salary);
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

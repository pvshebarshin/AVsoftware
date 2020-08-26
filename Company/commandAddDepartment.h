#ifndef COMMANDADDDEPARTMENT_H
#define COMMANDADDDEPARTMENT_H
#include "command.h"
#include "company.h"
#include <QString>

class CommandAddDepartment : public Command
{
public:
    CommandAddDepartment(Company *company, QString name);
    void execute() override;
    void undo() override;

private:
    QString departmentName;
    QString newName;
};
#endif

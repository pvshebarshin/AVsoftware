#ifndef CMDEDITDEPARTMENT_H
#define CMDEDITDEPARTMENT_H
#include "command.h"
#include "department.h"

class CommandEditDepartment : public Command
{
public:
    CommandEditDepartment(Company* company, Department* department, QString newName);
    void execute() override;
    void undo() override;

private:
    QString name;
    QString newName;
};

#endif

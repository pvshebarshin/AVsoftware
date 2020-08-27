#ifndef COMMANDREMOVEDEPARTMENT_H
#define COMMANDREMOVEDEPARTMENT_H
#include <QString>
#include"command.h"
#include"company.h"

class CommandRemoveDepartment : public Command
{
public:
    CommandRemoveDepartment(Company* company, Department* department);
    void undo() override;
    void execute() override;

private:
    QString departmentName;
    QMap<QString, Employee> employees;
};
#endif

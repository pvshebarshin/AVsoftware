#ifndef COMMANDADDDEPARTMENT_H
#define COMMANDADDDEPARTMENT_H
#include <QString>
#include "command.h"
#include "company.h"
class CommandAddDepartment : public Command
{
public:
    /*
    Конструктор команды добавления департамента
    */
    CommandAddDepartment(Company* company, QString name);

    /*
    Переопределенный метод родительского класса Command, добавляющий департамент
    */
    void execute() override;

    /*
    Переопределенный метод родительского класса Command, удаляющий добавленый департамент
    */
    void undo() override;

private:
    QString departmentName;
    QString newName;
};
#endif

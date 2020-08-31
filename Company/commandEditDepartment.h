#ifndef CMDEDITDEPARTMENT_H
#define CMDEDITDEPARTMENT_H
#include "command.h"
#include "department.h"
class CommandEditDepartment : public Command
{
public:
    /*
    Конструктор создания команды, рюдактирующей департамент
    */
    CommandEditDepartment(Company* company, Department* department, QString newName);

    /*
    Переопределенный метод родительского класса Command, редактирующий департамент
    */
    void execute() override;

    /*
    Переопределенный метод родительского класса Command, возвращающет
    отредактированные изменения в департаменте
    */
    void undo() override;

private:
    QString name;
    QString newName;
};
#endif

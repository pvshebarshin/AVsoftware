#ifndef COMMANDREMOVEDEPARTMENT_H
#define COMMANDREMOVEDEPARTMENT_H
#include <QString>
#include"command.h"
#include"company.h"
class CommandRemoveDepartment : public Command
{
public:
    /*
    Конструктор команды удаления департамента
    */
    CommandRemoveDepartment(Company* company, Department* department);

    /*
    Переопределенный метод родительского класса Command, удаляющий выбранный департамент
    */
    void execute() override;

    /*
    Переопределенный метод родительского класса Command, возвращающий удаленный департамент
    */
    void undo() override;

private:
    QString departmentName;
    QMap<int, Employee> employees;
};
#endif

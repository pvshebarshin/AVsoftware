#ifndef COMMANDREMOVEEMPLOYEE_H
#define COMMANDREMOVEEMPLOYEE_H
#include "command.h"
#include "company.h"
class CommandRemoveEmployee : public Command
{
public:
    /*
    Конструктор команды удаляющей работника
    */
    CommandRemoveEmployee(Company* company, Department* department, Employee* employee);

    /*
    Переопределенный метод родительского класса Command, удаляющий работника
    */
    void execute() override;

    /*
    Переопределенный метод родительского класса Command, возвращающий удаленного работника
    */
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

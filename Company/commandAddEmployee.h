#ifndef COMMANDADDEMPLOYEE_H
#define COMMANDADDEMPLOYEE_H
#include "command.h"
#include "company.h"
class CommandAddEmployee : public Command
{
public:
    /*
    Конструктор команды добавления работника
    */
    CommandAddEmployee(Company* company, Department* department,QString name,
                       QString surname, QString middleName, QString function , uint32_t salary);

    /*
    Переопределенный метод родительского класса Command, добавляющий работника
    */
    void execute() override;

    /*
    Переопределенный метод родительского класса Command, удаляющий добавленного работника
    */
    void undo() override;

private:
    QString departamentName;
    QString name;
    QString surname;
    QString middleName;
    QString function;
    int id;
    uint32_t salary;
};
#endif

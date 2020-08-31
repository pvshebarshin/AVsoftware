#ifndef COMMAND_H
#define COMMAND_H
#include "company.h"
class Command
{
public:
    /*
    Конструктор виртуального класса Command
    */
    Command(Company* company = nullptr, Department* department = nullptr, Employee* employee = nullptr);

    /*
    Диструктор виртуального класса Comand, заданый по умолчанию
    */
    virtual ~Command() = default;


    /*
    Абстрактный(виртуальный не определенный) метод выполнения команды
    */
    virtual void execute() = 0;

    /*
    Абстрактный(виртуальный не определенный) метод возврата выполнения команды
    */
    virtual void undo() = 0;

protected:
    Company* company;
    Department* department;
    Employee* employee;
};
#endif

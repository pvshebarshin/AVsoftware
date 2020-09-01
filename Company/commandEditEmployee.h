#ifndef COMMANDEDITEMPLOYEE_H
#define COMMANDEDITEMPLOYEE_H
#include "command.h"
#include "company.h"
class CommandEditEmployee : public Command
{
public:
    /*
    Конструктор команды редактирующей данные работника
    */
    CommandEditEmployee(Company* company, Department* department, Employee* employee,
        QString newName, QString newSurname, QString newMiddlename, QString newFunction, uint32_t newSalary);

    /*
    Переопределенный метод родительского класса Command, возвращающий изначальные данные работника
    */
    void execute() override;

    /*
    Переопределенный метод родительского класса Command, редактирующий данный работника компании
    */
    void undo() override;

private:
    QString departmentName;
    QString name;
    QString surname;
    QString middleName;
    QString function;
    int id;
    uint32_t salary;

    QString newName;
    QString newSurname;
    QString newMiddleName;
    QString newFunction;
    int newId;
    uint32_t newSalary;
};
#endif

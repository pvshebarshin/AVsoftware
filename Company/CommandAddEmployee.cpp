#include"commandAddEmployee.h"

CommandAddEmployee::CommandAddEmployee(Company *company, Department *department,
    QString name, QString surname, QString middleName, QString function, uint32_t salary)
    : Command(company, department)
{
    this->departamentName = department->getName();
    this->name = name;
    this->surname = surname;
    this->middleName = middleName;
    this->function = function;
    this->salary = salary;
    this->id = Employee::getId(name, surname, middleName, function, salary);
}

void CommandAddEmployee::execute()
{
    this->department = this->company->getDepartments()->value(this->departamentName);
    if(this->department->getEmployees()->count(this->id) == 0)
        this->employee = this->department->addEmployee(this->name, this->surname,
                                        this->middleName, this->function, this->salary);
}

void CommandAddEmployee::undo()
{
    this->department->removeEmployee(this->id);
}

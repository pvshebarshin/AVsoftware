#include "commandEditEmployee.h"

CommandEditEmployee::CommandEditEmployee(Company* company, Department* department, Employee* employee,
        QString newName, QString newSurname, QString newMiddleName,QString newFunction, int newSalary)
    :Command(company, department, employee)
{
    this->departmentName = department->getName();
    this->name = employee->getName();
    this->surname = employee->getSurname();
    this->middleName = employee->getMiddleName();
    this->function = employee->getFunction();
    this->salary = employee->getSalary();
    this->id = employee->getId();
    this->newName = newName;
    this->newSurname = newSurname;
    this->newMiddleName= newMiddleName;
    this->newFunction = newFunction;
    this->newSalary = newSalary;
    this->newId = newName + ' ' + newSurname + ' ' + newMiddleName;
}

void CommandEditEmployee::undo()
{
    this->department = this->company->getDepartments()->value(this->departmentName);
    this->employee = this->department->getEmployees()->value(this->newId);
    if(this->employee)
        this->department->editEmployee(this->newId, this->name, this->surname,
                            this->middleName, this->function, this->salary);
}

void CommandEditEmployee::execute()
{
    this->department = this->company->getDepartments()->value(this->departmentName);
    this->employee = this->department->getEmployees()->value(this->id);
    if(this->employee)
        this->department->editEmployee(this->id, this->newName, this->newSurname,
                            this->newMiddleName, this->newFunction, this->newSalary);
}

#include "commandRemoveEmployee.h"

CommandRemoveEmployee::CommandRemoveEmployee(Company* company,
        Department* department, Employee* employee)
        :Command(company, department, employee)
{
    this->departamentName = department->getName();
    this->name = employee->getName();
    this->surname = employee->getSurname();
    this->middleName = employee->getMiddleName();
    this->salary = employee->getSalary();
    this->id = employee->getId();
    this->function = employee->getFunction();
}

void CommandRemoveEmployee::execute()
{
    this->department = this->company->getDepartments()->value(this->departamentName);
    this->department->removeEmployee(this->id);
}

void CommandRemoveEmployee::undo()
{
    this->department = this->company->getDepartments()->value(this->departamentName);
    if(this->department->getEmployees()->count(this->id) == 0)
        this->department->addEmployee(this->name, this->surname, this->middleName,
                                      this->function, this->salary);
}

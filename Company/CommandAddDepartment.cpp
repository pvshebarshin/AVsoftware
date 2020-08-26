#include"commandAddDepartment.h"

CommandAddDepartment::CommandAddDepartment(Company *company, QString name) : Command()
{
    this->company = company;
    this->departmentName = name;
}

void CommandAddDepartment::execute()
{
    if(this->company->getDepartments()->count(this->departmentName) == 0)
        this->department = this->company->addDepartment(this->departmentName);
}

void CommandAddDepartment::undo()
{
    if(this->company->getDepartments()->count(this->departmentName) != 0)
        this->company->removeDepartment(this->departmentName);
}

#include "commandEditDepartment.h"

CommandEditDepartment::CommandEditDepartment(Company* company,
    Department* department, QString newName)
    :Command(company, department)
{
    this->name = department->getName();
    this->newName = newName;
}

void CommandEditDepartment::execute()
{
    this->department = this->company->getDepartments()->value(this->name);
    this->department->setName(this->newName);
    if(this->department)
        this->company->getDepartments()->remove(this->name);
    this->company->getDepartments()->insert(this->newName, this->department);
}

void CommandEditDepartment::undo()
{
    this->department = this->company->getDepartments()->value(this->newName);

    if(this->department)
        this->company->getDepartments()->remove(this->newName);
    this->department->setName(this->name);
    this->company->getDepartments()->insert(this->name, this->department);

}

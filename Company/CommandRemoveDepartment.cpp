#include"commandRemoveDepartment.h"

CommandRemoveDepartment::CommandRemoveDepartment(Company* company, Department* department): Command(company, department)
{
    this->departmentName = department->getName();

    QMap<QString, Employee*> map(*this->department->getEmployees());
    QMapIterator<QString, Employee*> iterator(map);

    while (iterator.hasNext())
    {
        iterator.next();
        this->employees.insert(iterator.key(), *iterator.value());
    }
}

void CommandRemoveDepartment::undo()
{
    if(this->company->getDepartments()->count(this->departmentName) == 0)
    {
        this->department = this->company->addDepartment(this->departmentName);
        QMapIterator<QString, Employee> iterator(this->employees);
        while (iterator.hasNext())
        {
            iterator.next();
            Employee employee = iterator.value();
            this->department->addEmployee(employee.getName(), employee.getSurname(),
                    employee.getMiddleName(), employee.getFunction(), employee.getSalary());
        }
    }
}

void CommandRemoveDepartment::execute()
{
    if(this->company->getDepartments()->count(this->departmentName) != 0)
        this->company->removeDepartment(this->departmentName);
}

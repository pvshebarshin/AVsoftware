#include "department.h"


Department::Department(QString name) noexcept: QStandardItem(name),
     averageSalary(0), countOfEmployers(0), salary(0)
{
    this->name = name;
    employees = new QMap<QString, Employee*>();
    setColumnCount(3);
}

Department::~Department() noexcept
{
    QMapIterator<QString, Employee*> i(*this->employees);
    while (i.hasNext())
    {
        i.next();
        removeEmployee(i.key());
    }
    this->employees->clear();
    delete  this->employees;
}

uint32_t Department::getAverageSalary() const noexcept
{
    return this->averageSalary;
}

uint32_t Department::getCountEmployees() const noexcept
{
    return this->countOfEmployers;
}

QString Department::getName() const noexcept
{
    return this->name;
}

QMap<QString, Employee *> *Department::getEmployees() const noexcept
{
    return  this->employees;
}

void Department::setName(QString name) noexcept
{
    this->name = name;
    setData(name, Qt::DisplayRole);
}

Employee *Department::addEmployee(QString name, QString surname,
                                  QString middleName, QString function, uint32_t salary) noexcept
{
    Employee *employee = new Employee(name, surname, middleName, function, salary);

    this->employees->insert(employee->getId(), employee);
    ++this->countOfEmployers;
    this->salary += salary;
    this->averageSalary = this->salary / this->countOfEmployers;
    this->appendRow(employee);

    employee->setData(surname + ' ' + name + ' ' + middleName, Qt::DisplayRole);
    QModelIndex in(model()->index(row() , 3));
    model()->setData(in, this->averageSalary, Qt::DisplayRole);
    return employee;
}

void Department::removeEmployee(QString id)
{
    Employee* employer = getEmployees()->value(id);

    this->salary -= employer->getSalary();
    --this->countOfEmployers;

    if(this->countOfEmployers > 0){
        this->averageSalary = this->salary / this->countOfEmployers;
    }else{
        this->averageSalary = 0;
    }

    if(model())
    {
        QModelIndex in(model()->index(row(), 3));
        model()->setData(in, this->averageSalary, Qt::DisplayRole);
    }
    this->removeRow(employer->row());

    this->employees->remove(id);
}

void Department::editEmployee(QString id, QString name, QString surname, QString middleName,
                              QString function, uint32_t salary)
{
    Employee* employer = this->employees->value(id);

    this->salary -= employer->getSalary();
    this->salary += salary;

    employer->setName(name);
    employer->setSurname(surname);
    employer->setMiddleName(middleName);
    employer->setFunction(function);
    employer->setSalary(salary);

    this->averageSalary = this->salary / this->countOfEmployers;

    QModelIndex in(model()->index(row() , 3));
    model()->setData(in, this->averageSalary, Qt::DisplayRole);

    QString ID = name + ' ' + surname + ' ' + middleName;

    if(employer)
        this->employees->remove(id);
    this->employees->insert(ID, employer);

    employer->setData(surname + ' ' + name + ' ' + middleName, Qt::DisplayRole);
}

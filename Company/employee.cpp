#include "employee.h"

Employee::Employee(QString name, QString surname, QString middleName,
                   QString function, uint32_t salary) noexcept
{
    this->name = name;
    this->surname = surname;
    this->middleName = middleName;
    this->function = function;
    this->salary = salary;
    this->id = name + ' ' + surname + ' ' + middleName;
}

QString Employee::getName() const noexcept
{
    return this->name;
}

QString Employee::getSurname() const noexcept
{
    return this->surname;
}

QString Employee::getMiddleName() const noexcept
{
    return this->middleName;
}

QString Employee::getFunction() const noexcept
{
    return this->function;
}

QString Employee::getId() const noexcept
{
    return this->id;
}

uint32_t Employee::getSalary() const noexcept
{
    return this->salary;
}

void Employee::setName(const QString &name) noexcept
{
    this->name = name;
}

void Employee::setSurname(const QString &surname) noexcept
{
    this->surname = surname;
}

void Employee::setMiddleName(const QString &middleName) noexcept
{
    this->middleName = middleName;
}

void Employee::setFunction(const QString &function) noexcept
{
    this->function = function;
}

void Employee::setSalary(uint32_t salary) noexcept
{
    this->salary = salary;
}

void Employee::setData(const QVariant &value, int role)
{
    QModelIndex in(model()->index(row() , 1, parent()->index()));
    model()->setData(in, function, role);

    QModelIndex in2(model()->index(row() , 2, parent()->index()));
    model()->setData(in2, salary, role);

    QStandardItem::setData(value, role);

    emitDataChanged();
}

void Employee::setId(const QString &id) noexcept
{
    this->id = id;
}

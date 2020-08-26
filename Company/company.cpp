#include "company.h"

Company::Company() noexcept: QStandardItemModel()
{
    QStringList list;
    list << "Отдел" << "Должность" << "Зарплата" << "Средняя ЗП";
    setHorizontalHeaderLabels(list);
    this->departments = new QMap<QString , Department*>();
}

Company::~Company() noexcept
{
    QMapIterator<QString, Department*> iter (*getDepartments());
    while(iter.hasNext())
        removeDepartment(iter.next().key());
    this->departments->clear();
}

uint32_t Company::size() const noexcept
{
    return this->departments->size();
}

QMap<QString, Department *> *Company::getDepartments() const noexcept
{
    return this->departments;
}

Department* Company::addDepartment(QString name) noexcept
{
    Department * department = new Department(name);
    this->departments->insert(name, department);
    this->appendRow(department);
    QModelIndex in(index(department->row() , 3));
    setData(in, department->getAverageSalary(), Qt::DisplayRole);
    return  department;
}

void Company::removeDepartment(QString name) noexcept
{
    int row = this->departments->value(name)->row();
    this->removeRow(row);
    this->departments->remove(name);
}

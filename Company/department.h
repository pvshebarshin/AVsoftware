#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <QMap>
#include <QObject>
#include "employee.h"

class Department : public QStandardItem
{
public:
    Department(QString name) noexcept;
    ~Department() noexcept;

    uint32_t getAverageSalary() const noexcept;
    uint32_t getCountEmployees() const noexcept;
    QString getName() const noexcept;
    QMap<QString, Employee*>* getEmployees() const noexcept;

    void setName(QString name) noexcept;

    Employee* addEmployee(QString name, QString surname, QString middleName,
                          QString function, uint32_t salary) noexcept;

    void removeEmployee(QString id);

    void editEmployee(QString id, QString name, QString surname,
                      QString middleName, QString function, uint32_t salary);

private:
    QMap<QString, Employee*>* employees;

    QString name;
    uint32_t averageSalary;
    uint32_t countOfEmployers;
    uint32_t salary;
};

#endif

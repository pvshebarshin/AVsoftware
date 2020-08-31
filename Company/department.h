#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <QMap>
#include <QObject>
#include "employee.h"

class Department : public QStandardItem
{
public:
    /*
    Конструктор департамента
    */
    Department(QString name) noexcept;

    /*Деструктор департамента*/
    ~Department() noexcept;

    /*
    Возврат средней зарплаты по департаменту
    */
    uint32_t getAverageSalary() const noexcept;

    /*
    Возврат количества сотрудников в департаменте
    */
    uint32_t getCountEmployees() const noexcept;

    /*
    Возврат имени департамента
    */
    QString getName() const noexcept;

    /*
    Дает доступ к указателю на map из работников
    */
    QMap<QString, Employee*>* getEmployees() const noexcept;

    /*
    Устанавливает имя департамента
    */
    void setName(QString name) noexcept;

    /*
    Добавляет работника в департамент(в map)
    */
    Employee* addEmployee(QString name, QString surname, QString middleName,
                          QString function, uint32_t salary) noexcept;

    /*
    Удаляет работника из департамента(из map)
    */
    void removeEmployee(QString id);

    /*
    Редактирование данных работника департамента
    */
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

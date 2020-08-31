#ifndef COMPANY_H
#define COMPANY_H
#include <QObject>
#include <QStandardItemModel>
#include "department.h"

class Company : public QStandardItemModel
{
    Q_OBJECT

public:
    /*
    Конструктор компании
    */
    Company() noexcept;
    /*
    Деструктор компании
    */
    ~Company() noexcept;

    /*
    Предоставление доступа к узадателю на map из департаментов
    */
    QMap<QString, Department*>* getDepartments() const noexcept;

    /*
    Добавление департамента в map
    */
    Department* addDepartment(QString name) noexcept;

    /*
    Удаление департамента из map
    */
    void removeDepartment(QString name) noexcept;

private:
    QMap<QString, Department*>* departments;
};
#endif

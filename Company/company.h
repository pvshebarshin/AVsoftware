#ifndef COMPANY_H
#define COMPANY_H
#include <QObject>
#include <QStandardItemModel>
#include "department.h"

class Company : public QStandardItemModel
{
    Q_OBJECT

public:
    Company() noexcept;
    ~Company() noexcept;

    uint32_t size() const noexcept;
    QMap<QString, Department*>* getDepartments() const noexcept;

    Department* addDepartment(QString name) noexcept;

    void removeDepartment(QString name) noexcept;

private:
    QMap<QString , Department*>* departments;
};
#endif

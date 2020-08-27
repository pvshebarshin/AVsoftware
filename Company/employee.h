#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QStandardItem>

class Employee : public QStandardItem
{
public:
    Employee(QString name, QString surname, QString middleName,
             QString function, uint32_t salary) noexcept;

    QString getName() const noexcept;
    QString getSurname() const noexcept;
    QString getMiddleName() const noexcept;
    QString getFunction() const noexcept;
    QString getId() const noexcept;
    uint32_t getSalary() const noexcept;

    void setName(const QString &name) noexcept;
    void setSurname(const QString &surname) noexcept;
    void setMiddleName(const QString &middleName) noexcept;
    void setFunction(const QString &function) noexcept;
    void setSalary(uint32_t salary) noexcept;
    void setData(const QVariant &value, int role = Qt::UserRole + 1);
    void setId(const QString &id);

private:
    QString name;
    QString surname;
    QString middleName;
    QString function;
    QString id;
    uint32_t salary;
};

#endif

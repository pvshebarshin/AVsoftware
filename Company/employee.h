#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QStandardItem>
class Employee : public QStandardItem
{
public:
    /*
    Конструктор класса работника
    */
    Employee(QString name = "", QString surname = "", QString middleName = "",
             QString function = "", uint32_t salary = 0) noexcept;

    /*
    Получение имени работника
    */
    QString getName() const noexcept;

    /*
    Получение фамилии работника
    */
    QString getSurname() const noexcept;

    /*
    Получение отчества работника
    */
    QString getMiddleName() const noexcept;

    /*
    Получение должности работника
    */
    QString getFunction() const noexcept;

    /*
    Получение уникального идентифекатора работника
    */
    int getId() const noexcept;
    static int getId(QString name, QString surname, QString middleName,
                     QString function, uint32_t salary) noexcept;

    /*
    Получение зарплаты работника
    */
    uint32_t getSalary() const noexcept;

    /*
    Установка имени работника
    */
    void setName(const QString &name) noexcept;

    /*
    Установка фамилии работника
    */
    void setSurname(const QString &surname) noexcept;

    /*
    Установка отчества работника
    */
    void setMiddleName(const QString &middleName) noexcept;

    /*
    Установка должности работника
    */
    void setFunction(const QString &function) noexcept;

    /*
    Установка зарплаты работника
    */
    void setSalary(uint32_t salary) noexcept;

    /*
    Заполнение treeview данными о работнике
    */
    void setData(const QVariant &value, int role = Qt::UserRole + 1) override;

    /*
    Установка уникального идентификатора рабочего
    */
    void setId(const int &id) noexcept;

private:
    QString name;
    QString surname;
    QString middleName;
    QString function;
    int id;
    uint32_t salary;
};
#endif

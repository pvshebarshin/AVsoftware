#ifndef EMPLOYEECREATOR_H
#define EMPLOYEECREATOR_H
#include <QDialog>
#include <QRegExpValidator>
#include <QStringList>
#include "employee.h"

namespace Ui {
class EmployeeEditor;
}

class EmployeeEditor : public QDialog
{
    Q_OBJECT

public:
     EmployeeEditor(Employee* employee = 0, QWidget *parent = 0);
    ~EmployeeEditor();
    QStringList getData();

private:
    Employee* employee;
    Ui::EmployeeEditor* ui;
};
#endif

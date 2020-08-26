#include "employeecreator.h"
#include "ui_employeeeditor.h"

EmployeeEditor::EmployeeEditor(Employee *employee, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeEditor)
{
    this->ui->setupUi(this);

    setModal(true);
    this->employee = employee;

    this->ui->lineName->setValidator(new QRegExpValidator(QRegExp("[A-Я]{0,20}",Qt::CaseInsensitive)));
    this->ui->lineSurname->setValidator(new QRegExpValidator(QRegExp("[A-Я]{0,20}",Qt::CaseInsensitive)));
    this->ui->lineSurname->setFocus();
    this->ui->lineMiddleName->setValidator(new QRegExpValidator(QRegExp("[A-Я]{0,20}",Qt::CaseInsensitive)));
    this->ui->lineSalary->setValidator(new QRegExpValidator(QRegExp("[1-9]{1}[0-9]{2,15}")));

    if(this->employee != nullptr)
    {
        this->ui->lineName->setText(employee->getName());
        this->ui->lineSurname->setText(employee->getSurname());
        this->ui->lineMiddleName->setText(employee->getMiddleName());
        this->ui->lineFunction->setText(employee->getFunction());
        this->ui->lineSalary->setText(QString::number(employee->getSalary()));
    }
}

EmployeeEditor::~EmployeeEditor()
{
    delete this->ui;
}

QStringList EmployeeEditor::getData()
{
    QStringList data;
    data.append(this->ui->lineName->text());
    data.append(this->ui->lineSurname->text());
    data.append(this->ui->lineMiddleName->text());
    data.append(this->ui->lineFunction->text());
    data.append(QString::number(this->ui->lineSalary->text().toInt()));
    return data;
}

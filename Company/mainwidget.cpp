#include "mainwidget.h"
#include <department.h>
#include <ui_centralwidget.h>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CentralWidget)
{
    ui->setupUi(this);
    ui->view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->buttonAddEmploee->setDisabled(true);
    ui->buttonRemoveEmploee->setDisabled(true);
    ui->buttonRemoveDepartment->setDisabled(true);

    connect(ui->buttonAddEmploee, SIGNAL(clicked()), this, SIGNAL(addEmployee()));
    connect(ui->buttonRemoveEmploee, SIGNAL(clicked()), this, SIGNAL(removeEmployee()));
    connect(ui->buttonRemoveDepartment, SIGNAL(clicked()), this, SIGNAL(removeDepartment()));
}

void CentralWidget::sendAddDepartment()
{
    QString str = ui->lineNameDepartmnt->text().trimmed();
    emit addDepartment(str);
}

void CentralWidget::sendEditDepartment()
{
    QString str = ui->lineName->text().trimmed();
    emit editDepartment(str);
}

void CentralWidget::setEnableButtons()
{
    if(ui->view->selectionModel()->hasSelection()){
        current = ui->view->selectionModel()->selectedIndexes().first().siblingAtColumn(0);
        if(current.parent() == QModelIndex()){
            ui->buttonAddEmploee->setEnabled(true);
            ui->buttonRemoveDepartment->setEnabled(true);
            ui->buttonRemoveEmploee->setEnabled(false);
            emit currentDepartment(current);
        }else{
            ui->buttonAddEmploee->setEnabled(false);
            ui->buttonRemoveEmploee->setEnabled(true);
            ui->buttonRemoveDepartment->setEnabled(false);
            emit currentDepartment(current.parent());
            emit currentEmployee(current);
        }
    }else{
        current = QModelIndex();
        ui->buttonAddEmploee->setEnabled(false);
        ui->buttonRemoveEmploee->setEnabled(false);
        ui->buttonRemoveDepartment->setEnabled(false);
    }
}

QModelIndex CentralWidget::currentIndex() const
{
    return current;
}

void CentralWidget::setDep(QString name , uint32_t count, uint32_t salary)
{
    ui->lineName->setText(name.trimmed());
    ui->lCount->setText(QString::number(count));
    ui->lSalary->setText(QString::number(salary));
}

QTreeView *CentralWidget::view()
{
    return ui->view;
}

CentralWidget::~CentralWidget()
{
    delete ui;
}

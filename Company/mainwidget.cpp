#include "mainwidget.h"
#include <department.h>
#include <ui_mainwidget.h>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget)
{
    this->ui->setupUi(this);
    this->ui->view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->ui->buttonAddEmploee->setDisabled(true);
    this->ui->buttonRemoveEmploee->setDisabled(true);
    this->ui->buttonRemoveDepartment->setDisabled(true);

    connect(this->ui->buttonAddEmploee, SIGNAL(clicked()), this, SIGNAL(addEmployee()));
    connect(this->ui->buttonRemoveEmploee, SIGNAL(clicked()), this, SIGNAL(removeEmployee()));
    connect(this->ui->buttonRemoveDepartment, SIGNAL(clicked()), this, SIGNAL(removeDepartment()));
}

void MainWidget::sendAddDep()
{
    QString str = this->ui->lineNameDepartmnt->text().trimmed();
    emit addDepartment(str);
}

void MainWidget::sendEditDep()
{
    QString str = this->ui->lineName->text().trimmed();
    emit editDepartment(str);
}

void MainWidget::setEnableButtons()
{
    if(this->ui->view->selectionModel()->hasSelection()){
        this->current = this->ui->view->selectionModel()->selectedIndexes().first().siblingAtColumn(0);
        if(current.parent() == QModelIndex()){
            this->ui->buttonAddEmploee->setEnabled(true);
            this->ui->buttonRemoveDepartment->setEnabled(true);
            this->ui->buttonRemoveEmploee->setEnabled(false);
            emit currentDepartment(this->current);
        }else{
            this->ui->buttonAddEmploee->setEnabled(false);
            this->ui->buttonRemoveEmploee->setEnabled(true);
            this->ui->buttonRemoveDepartment->setEnabled(false);
            emit currentDepartment(this->current.parent());
            emit currentEmployee(this->current);
        }
    }else{
        this->current = QModelIndex();
        this->ui->buttonAddEmploee->setEnabled(false);
        this->ui->buttonRemoveEmploee->setEnabled(false);
        this->ui->buttonRemoveDepartment->setEnabled(false);
    }
}


void MainWidget::setDep(QString name , uint32_t count, uint32_t salary)
{
    this->ui->lineName->setText(name.trimmed());
    this->ui->lableCount->setText(QString::number(count));
    this->ui->lableSalary->setText(QString::number(salary));
}

QTreeView *MainWidget::view() const noexcept
{
    return this->ui->view;
}

MainWidget::~MainWidget()
{
    delete this->ui;
}

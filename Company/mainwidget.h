#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QObject>
#include <QtWidgets>

namespace Ui
{
    class CentralWidget;
}

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget *parent = 0);
    ~CentralWidget();

    QTreeView *view();

    QModelIndex currentIndex() const;

    void setDep(QString name, uint32_t count, uint32_t salary);

signals:
    void addEmployee();
    void removeEmployee();

    void addDepartment(QString);
    void editDepartment(QString);
    void removeDepartment();

    void currentDepartment(const QModelIndex &index);
    void currentEmployee(const QModelIndex &index);

public slots:
    void setEnableButtons();
    void sendAddDep();
    void sendEditDep();

private:
     Ui::CentralWidget* ui;
     QModelIndex current;
};

#endif

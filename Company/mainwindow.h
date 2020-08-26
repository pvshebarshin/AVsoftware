#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "company.h"
#include "commandAddDepartment.h"
#include "commandRemoveDepartment.h"
#include "commandAddEmployee.h"
#include "commandRemoveEmployee.h"
#include "commandEditEmployee.h"
#include "commandEditDepartment.h"
#include "mainwidget.h"
#include "employeecreator.h"
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>
#include <QFile>
#include <QtXml>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = 0) noexcept;
    ~MainWindow() noexcept;

public slots:
    void setCurrentDepartment(const QModelIndex &index);
    void setCurrentEmployee(const QModelIndex &index);

    void addDepartment(QString name);
    void addEmployee();

    void editDepartment(QString name);
    void editCompany(const QModelIndex &index);

    void removeDepartment();
    void removeEmployee();

    void openFile();
    void openNewCompanyDialog();
    void openNewEployeeDialog();

    void newCompany();

private:
    Company* company;
    Department* currentDepartment;
    Employee* currentEmployee;
    QList<Command*> history;
    QListIterator<Command*> iterator;
    CentralWidget* centralWidget;
    EmployeeEditor* employeeEditor;
    QUrl path;

    void executeCommand(Command* command);
    void undoCommand();
    void redoCommand();
    void clearHistory();
    void createActions();
    void editEmployee();
    void saveFile();
};

#endif

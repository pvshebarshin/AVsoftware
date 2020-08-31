#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QObject>
#include <QtWidgets>
#include <QFile>
#include <QtXml>
#include "company.h"
#include "commandAddDepartment.h"
#include "commandRemoveDepartment.h"
#include "commandAddEmployee.h"
#include "commandRemoveEmployee.h"
#include "commandEditEmployee.h"
#include "commandEditDepartment.h"
#include "mainwidget.h"
#include "employeecreator.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*
    Конструктор для создания основного окна приложения
    */
     MainWindow(QWidget *parent = 0) noexcept;

    /*
    Деструктор основного окна приложения
    */
    ~MainWindow() noexcept;

public slots:
    /*
    Сигнал выбора текущего департамента
    */
    void setCurrentDepartment(const QModelIndex &index);

    /*
    Слот выбора текущего работника
    */
    void setCurrentEmployee(const QModelIndex &index);

    /*
    Слот для добавления департамента
    */
    void addDepartment(QString name);

    /*
    Слот для добавления работника
    */
    void addEmployee();

    /*
    Слот для редактирования департамента
    */
    void editDepartment(QString name);

    /*
    Слот для отработки логики работы при двойном клике по treeview
    */
    void editCompany(const QModelIndex &index);

    /*
    Слот выполняющий команду удаления департамента из компании
    */
    void removeDepartment();

    /*
    Слот выполняющий команду удаления работника
    */
    void removeEmployee();

    /*
    Открытие файла и чтение xml
    */
    void openFile();


    /*
    Создание новго файла для работы с xml
    */
    void openNewCompanyDialog();

    /*
    Открытие нового окна для создание нового работника
    */
    void openNewEployeeDialog();

    /*
    Создание новой компании при считывании или создании файла
    */
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

    /*
    Выполнение команды(Реализация паттерна команда)
    */
    void executeCommand(Command* command);

    /*
    Откат команды(отмена)
    */
    void undoCommand();

    /*
    Возврат отката команды(отмена отмены)
    */
    void redoCommand();

    /*
    Удаление истории команд для undo redo
    */
    void clearHistory();

    /*
     Создание пунктов меню для взаимодействия с файлами
    */
    void createActions();

    /*
    Изменение данных работника компании
    */
    void editEmployee();

    /*
    Сохронение измененного xml файла
    */
    void saveFile();
};
#endif

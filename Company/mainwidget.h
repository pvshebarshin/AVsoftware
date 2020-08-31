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
    /*
    Конструктор создающий treeview и логику работы с ним
    */
    CentralWidget(QWidget *parent = 0);

    /*
    Деструктор, удаляющий ui
    */
    ~CentralWidget();

    /*
    Возврат ссылки на treeview
    */
    QTreeView* view() const noexcept;

    /*
    Вывод данных о департаменте
    */
    void setDep(QString name, uint32_t count, uint32_t salary);

    /*
    Объявление необходимых сигналов
    */
signals:
    void addEmployee();
    void removeEmployee();

    void addDepartment(QString);
    void editDepartment(QString);
    void removeDepartment();

    void currentDepartment(const QModelIndex &index);
    void currentEmployee(const QModelIndex &index);

public slots:
    /*
    Дизейбл кнопок в зависимости от выбрановых элементов treeview
    */
    void setEnableButtons();

    /*
    Слот для добавления нового департамента
    */
    void sendAddDep();

    /*
    Слот для редактирования департамента
    */
    void sendEditDep();

private:
     Ui::CentralWidget* ui;
     QModelIndex current;
};
#endif

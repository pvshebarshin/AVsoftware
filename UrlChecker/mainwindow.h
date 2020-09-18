#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "URL.h"

#include <QList>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    Ui::MainWindow *ui;
    QList<URL> urls;
    QNetworkAccessManager* manager;
    QTimer* timer;

private slots:
    void replyFinished(QNetworkReply* reply);
    void openFile();
    void on_beginButton_clicked();
    void on_exitButton_clicked();
    void on_time_textChanged(const QString &arg1);
    void onTimeOut();
};
#endif

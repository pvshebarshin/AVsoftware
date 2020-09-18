#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->beginButton->setEnabled(false);
    this->ui->exitButton->setEnabled(false);
    this->ui->time->setValidator(new QRegExpValidator(QRegExp("[1-9]{1}[0-9]{0,15}")));
    this->timer = new QTimer(this);
    createActions();
    this->manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));
    QAction *open= new QAction(tr("Открыть"));
    open->setShortcuts(QKeySequence::Open);
    open->setStatusTip(tr("Открыть файл"));
    connect(open, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(open);
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    reply->deleteLater();
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QString status = status_code.toString();
    qDebug() << status << (reply->url().toString() == urls[0].getName());
    if(urls[0].isNewCode(status))
    {
        this->ui->table->setItem(0, 2, new QTableWidgetItem(QString::number(urls[0].getTime())));
       urls[0].newTime();
    } else {
        urls[0].addInterval();
    }
    urls[0].setCode(status);
    this->ui->table->setItem(0, 1, new QTableWidgetItem(urls[0].getCode()));
    timer->start(this->ui->time->text().toInt());
}

void MainWindow::openFile()
{
    QUrl path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("XML files (*.xml)"));
    QFile xmlFile(path.toString());
    if(!path.isEmpty() && xmlFile.open(QIODevice::ReadOnly))
    {
        this->urls.clear();
        this->ui->table->clear();
        QXmlStreamReader reader(&xmlFile);
        QString name;
        while (!reader.atEnd() && reader.readNext())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "urls"){

                } else if(reader.name() == "url") {
                    this->urls.append(URL(reader.attributes().value("name").toString().trimmed()));
                }
            }
        }
        this->ui->table->setRowCount(this->urls.count());
        this->ui->table->setColumnCount(3);
        for(int i = 0; i < this->urls.count(); ++i)
        {
            QTableWidgetItem* item = new QTableWidgetItem(this->urls[i].getName());
            this->ui->table->setItem(i, 0, item);
            this->ui->table->setItem(i, 1, new QTableWidgetItem("---"));
            this->ui->table->setItem(i, 2, new QTableWidgetItem("---"));
        }
        this->ui->table->setHorizontalHeaderLabels(QStringList()
                        << "URL" << "Код ответа" << "Время изменения статуса");
        this->ui->beginButton->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete timer;
}

void MainWindow::on_beginButton_clicked()
{
    this->statusBar()->clearMessage();
    if(this->ui->time->text() == "")
    {
        this->statusBar()->showMessage("Вы должны ввести таймаут проверки доступности");
        return;
    }

    this->ui->time->setEnabled(false);
    this->ui->beginButton->setEnabled(false);
    this->ui->exitButton->setEnabled(true);

    for(int i = 0; i < urls.count(); i++)
        urls[i].setInterval(this->ui->time->text().toInt());

    this->manager->get(QNetworkRequest(urls[0]));
}

void MainWindow::on_exitButton_clicked()
{
    this->ui->beginButton->setEnabled(true);
    this->ui->exitButton->setEnabled(false);
    this->ui->time->setEnabled(true);
    timer->stop();
    qDebug() << "stop";
}

void MainWindow::on_time_textChanged(const QString &arg1)
{
    this->statusBar()->clearMessage();
}

void MainWindow::onTimeOut()
{
    this->manager->get(QNetworkRequest(urls[0]));
}

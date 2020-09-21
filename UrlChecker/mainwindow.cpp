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
    createActions();
}

void MainWindow::createActions() noexcept
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));
    QAction *open= new QAction(tr("Открыть"));
    open->setShortcuts(QKeySequence::Open);
    open->setStatusTip(tr("Открыть файл"));
    connect(open, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(open);
}

void MainWindow::openFile()
{
    QUrl path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("XML files (*.xml)"));
    QFile xmlFile(path.toString());
    if(!path.isEmpty() && xmlFile.open(QIODevice::ReadOnly))
    {
//        QString regexp = "^(((http|ftp)(s?)://)|(www.))(([a-zA-Z0-9-.]+(.[a-zA-Z0-9-.]+)+)|localhost)(/?)([a-zA-Z0-9-.?,'/\+&%$#_])?([\d\w./%+-=&amp;?:\&quot;',|~;])$";
//        QRegExp regx(regexp);
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
//                    if(regx.exactMatch(reader.attributes().value("name").toString().trimmed()))
                    this->urls.append(URL(reader.attributes().value("name").toString().trimmed()));
                }
            }
        }

        for(int i = 0; i < urls.count(); ++i)
            if(!urls[i].isValid())
                urls.removeOne(urls[i]);

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
        this->ui->table->resizeColumnsToContents();
        this->ui->beginButton->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_beginButton_clicked()
{
    this->statusBar()->clearMessage();
    if(this->ui->time->text() == "")
    {
        this->statusBar()->showMessage("Вы должны ввести таймаут проверки доступности");
        return;
    }

    if(!ui->radioButton_ms->isChecked() && !ui->radioButton_s->isChecked() && !ui->radioButton_ns->isChecked())
    {
        this->statusBar()->showMessage("Вы должны  выбрать измерение времени");
        return;
    }

    this->ui->time->setEnabled(false);
    this->ui->beginButton->setEnabled(false);
    this->ui->exitButton->setEnabled(true);

    for(int i = 0; i < urls.count(); ++i)
    {
        urls[i].setInterval(this->ui->time->text().toInt());
        connectors.append(new HTTPconnector());
        ui->radioButton_s->isChecked() ? connectors[i]->setMarker("S") :
                    ui->radioButton_ms->isChecked() ? connectors[i]->setMarker("MS") :
                                connectors[i]->setMarker("US");
    }

    for(int i = 0; i < urls.count(); ++i)
    {
        connectors[i]->setIndex(i);
        connectors[i]->setURL(&urls[i]);
        connectors[i]->setInterval(this->ui->time->text().toInt());
        connectors[i]->setStop(false);
        connect(connectors[i], SIGNAL(addToTable(QString, int, int)), this, SLOT(addToTable(QString, int, int)));
        connectors[i]->start();
    }
}

void MainWindow::on_exitButton_clicked()
{
    this->ui->beginButton->setEnabled(true);
    this->ui->exitButton->setEnabled(false);
    this->ui->time->setEnabled(true);
    for(int i = 0; i < urls.count(); ++i)
        connectors[i]->setStop(true);
}

void MainWindow::on_time_textChanged(const QString &arg1)
{
    this->statusBar()->clearMessage();
}

void MainWindow::addToTable(QString str, int time, int index)
{
    if(time == -1 && str != ""){
        this->ui->table->setItem(index, 1, new QTableWidgetItem(str));
    }else if(time != -1 && str != ""){
        this->ui->table->setItem(index, 1, new QTableWidgetItem(str));
        this->ui->table->setItem(index, 2, new QTableWidgetItem(QString::number(time)));
    } else if(time == -1 && str == ""){
        this->ui->table->setItem(index, 1, new QTableWidgetItem("Ошибка подключения"));
    } else {
        this->ui->table->setItem(index, 1, new QTableWidgetItem(str));
        this->ui->table->setItem(index, 2, new QTableWidgetItem(QString::number(time)));
    }
}

void MainWindow::on_redButton_clicked()
{
    for(int i = 0; i < urls.count(); ++i)
        connectors[i]->setStop(true);
    this->close();
}

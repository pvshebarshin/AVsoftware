#ifndef HTTPCONNECTOR_H
#define HTTPCONNECTOR_H
#include "URL.h"
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QTime>

//Класс подключающийся по HTTP к сайту в отдельном потоке
class HTTPconnector : public QThread
{
    Q_OBJECT
public:
    explicit HTTPconnector(QObject *parent = 0);
    ~HTTPconnector();

    //Основной переопределнный метод класса QThread
    //для работы с http
    void run() override;

    //Сеттеры для установки необходимых двнных
    void setStop(bool stop) noexcept;
    void setIndex(int index) noexcept;
    void setInterval(int interval) noexcept;
    void setURL(URL* url) noexcept;
    void setMarker(QString marker);


signals:
    //сигнал отправляющийся после обработкт запроса для записи в таблицу
    void addToTable(QString str, int time, int index);

private:
    URL* url;
    int index;
    int interval;
    bool stop;
    QString marker;
};

#endif

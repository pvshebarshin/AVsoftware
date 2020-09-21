#ifndef HTTPCONNECTOR_H
#define HTTPCONNECTOR_H

#include "URL.h"

#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QTime>

class HTTPconnector : public QThread
{
    Q_OBJECT
public:
    explicit HTTPconnector(QObject *parent = 0);
    ~HTTPconnector();

    void run();
    void setStop(bool stop) noexcept;
    void setIndex(int index) noexcept;
    void setInterval(int interval) noexcept;
    void setURL(URL* url) noexcept;


signals:
    void addToTable(QString str, int time, int index);

private:
    URL* url;
    int index;
    int interval;
    bool stop;
};

#endif

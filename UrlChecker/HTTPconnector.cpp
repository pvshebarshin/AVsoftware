#include "HTTPconnector.h"
#include <QtCore>

HTTPconnector::HTTPconnector(QObject *parent) : QThread(parent)
{

}

HTTPconnector::~HTTPconnector()
{

}

void HTTPconnector::run()
{
    QNetworkAccessManager* connection;
    while(true)
    {
        qDebug() << "run " << index << *url;

        QEventLoop waitLoop;
        connection = new QNetworkAccessManager();
        QNetworkReply *reply = connection->get(QNetworkRequest(*url));
        QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
        waitLoop.exec();

        QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        QString status = status_code.toString();
        qDebug() << status << QString::number(this->index);
        if(url->isNewCode(status)){
            int temp = url->getTime();
            url->newTime();
            url->setCode(status);
            emit addToTable(status, temp, this->index);
        } else {
            url->setCode(status);
            url->addInterval();
            emit addToTable(status, -1, this->index);
        }

        msleep(interval);
        if(stop){
            delete reply;
            delete connection;
            return;
        }
        delete reply;
    }
}

void HTTPconnector::setStop(bool stop) noexcept
{
    this->stop = stop;
}

void HTTPconnector::setIndex(int index) noexcept
{
    this->index = index;
}

void HTTPconnector::setInterval(int interval) noexcept
{
    this->interval = interval;
}

void HTTPconnector::setURL(URL *url) noexcept
{
    this->url = url;
}

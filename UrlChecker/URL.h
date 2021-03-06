#ifndef URL_H
#define URL_H
#include <QString>
#include <QUrl>

class URL : public QUrl
{
public:
    URL(QString name) noexcept;

    //гетеры
    QString getName() const noexcept;
    QString getCode() const noexcept;
    int getTime() const noexcept;

    //сетеры
    void setCode(QString code) noexcept;
    void setInterval(int interval) noexcept;

    //прибавляет время изменения ответа
    void addInterval() noexcept;

    //после изменения ответа обнуляем время
    void newTime() noexcept;

    //метод проверяет изменился ли код ответы
    bool isNewCode(QString code) const noexcept;

private:
    QString name;
    QString code = "";
    int dTime = 0;
    int interval = 0;
};

#endif

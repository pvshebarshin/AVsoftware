#ifndef URL_H
#define URL_H
#include <QString>
#include <QUrl>

class URL : public QUrl
{
public:
    URL(QString name) noexcept;

    QString getName() const noexcept;
    QString getCode() const noexcept;
    int getTime() const noexcept;

    void setCode(QString code) noexcept;
    void setInterval(int interval) noexcept;

    void addInterval() noexcept;
    void newTime() noexcept;
    bool isNewCode(QString code) const noexcept;

private:
    QString name;
    QString code = "";
    int dTime = 0;
    int interval = 0;
};

#endif

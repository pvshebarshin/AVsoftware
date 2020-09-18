#include "URL.h"


URL::URL(QString name) noexcept : QUrl(name)
{
    this->name = name;
}

QString URL::getName() const noexcept
{
    return this->name;
}

QString URL::getCode() const noexcept
{
    return this->code;
}

int URL::getTime() const noexcept
{
    return this->dTime;
}

void URL::setCode(QString code) noexcept
{
    this->code = code;
}

void URL::setInterval(int interval) noexcept
{
    this->interval = interval;
}

void URL::addInterval() noexcept
{
    this->dTime += this->interval;
}

void URL::newTime() noexcept
{
    this->dTime = 0;
}

bool URL::isNewCode(QString code) const noexcept
{
    return code != this->code;
}

#ifndef HMESSAGE_H
#define HMESSAGE_H
#include <QString>

class Hmessage
{
private:
    const QString _body;
    const QString _date;
    const QString _time;
    const QString _src;
    const QString _dst;
public:
    Hmessage(QString body,QString date,QString time,QString src,QString dst);
    QString get_body() const;
    QString get_date() const;
    QString get_time() const;
    QString get_src () const;
    QString get_dst () const;
};

#endif // HMESSAGE_H

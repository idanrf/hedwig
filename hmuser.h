#ifndef HMUSER_H
#define HMUSER_H
#include <QVector>
#include <QString>
#include "hdestination.h"

class HmUser
{
private:
    const QString _username;
    const QString _password;
    const QString _token;
    const QString _firstName;
    const QString _lastName;
    QVector <Hdestination *> _dsts;
public:
    HmUser(QString username,QString password,QString token,QString firstName,QString lastName);
    QString get_username()  const;
    QString get_password()  const;
    QString get_token()     const;
    QString get_firstName() const;
    QString get_lastName()  const;


    void add_dst(Hdestination * temp);

};

#endif // HMUSER_H

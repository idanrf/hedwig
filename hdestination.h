#ifndef HDESTINATION_H
#define HDESTINATION_H
#include <QPushButton>
#include "hmessage.h"

#include <QVector>
#include <QString>
#include <sstream>



class Hdestination :public QPushButton
{
private:
     const QString _ID;
     const QString _name;
     const QString _type;
     QVector <Hmessage> _messages;

public:
    Hdestination(QString id,QString name,QString type);
    Hmessage get_message(int i)  const ;
    QString get_ID() const;
    QString get_name() const;
    QString get_type() const;

};


class Hchannel: public Hdestination
{
public:
    Hchannel(QString id,QString name);
};

class Hgroup: public Hdestination
{
public:
    Hgroup(QString id,QString name);
};

class Huser: public Hdestination
{
public:
    Huser(QString id,QString name);
};

#endif // HDESTINATION_H

#include "hdestination.h"

Hdestination::Hdestination(QString id,QString name,QString type)
    : _ID(id),_name(name),_type(type)
{

}
Hmessage Hdestination::get_message(int i)  const { return _messages[i]; }
QString  Hdestination::get_ID()            const{ return _ID; }
QString  Hdestination::get_name()          const{ return _name; }
QString  Hdestination::get_type()          const{ return _type; }

Hchannel::Hchannel(QString id,QString name):Hdestination(id,name,"CHANNEL")
{

}

Hgroup::Hgroup(QString id,QString name):Hdestination(id,name,"GROUP")
{

}

Huser::Huser(QString id,QString name):Hdestination(id,name,"USER")
{

}

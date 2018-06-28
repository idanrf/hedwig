#include "hmessage.h"

Hmessage::Hmessage(QString body,QString date,QString time,QString src,QString dst)
    :_body(body),_date(date),_time(time),_src(src),_dst(dst)
{

}

QString Hmessage::get_body() const{ return _body; }
QString Hmessage::get_date() const{ return _date; }
QString Hmessage::get_time() const{ return _time; }
QString Hmessage::get_src () const{ return _src;  }
QString Hmessage::get_dst () const{ return _dst;  }

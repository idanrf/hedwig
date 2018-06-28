#include "hmuser.h"

HmUser::HmUser(QString username,QString password,QString token,QString firstName,QString lastName)
    :_username(username),_password(password),_token(token),_firstName(firstName),_lastName(lastName)
{

}

QString HmUser::get_username() const { return _username; }
QString HmUser::get_password() const { return _password; }
QString HmUser::get_token()    const { return _token; }
QString HmUser::get_firstName()const { return _firstName; }
QString HmUser::get_lastName() const { return _lastName; }

void HmUser::add_dst(Hdestination * temp)
{
    _dsts.push_back(temp);
}

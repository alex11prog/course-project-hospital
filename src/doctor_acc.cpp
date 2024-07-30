#include "inc/doctor_acc.h"

doctor_acc::doctor_acc()
{

}

void doctor_acc::set_login(QString login)
{
this->login = login;
}

void doctor_acc::set_password(QString password)
{
this->password = password;
}

QString doctor_acc::get_login()
{
return login;
}

QString doctor_acc::get_password()
{
    return password;
}

void doctor_acc::set_position(QString position)
{
this->position = position;
}

QString doctor_acc::get_position()
{
return position;
}

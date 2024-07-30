#include "inc/human.h"

human::human()
{

}

void human::set_id(int id)
{
this->id = id;
}

int human::get_id()
{
    return id;
}

void human::set_surname(QString surname)
{
this->surname = surname;
}

QString human::get_surname()
{
return surname;
}

void human::set_name(QString name)
{
this->name = name;
}

QString human::get_name()
{
return name;
}

void human::set_patronymic(QString patronymic)
{
this->patronymic = patronymic;
}

QString human::get_patronymic()
{
return patronymic;
}

void human::set_gender(QString gender)
{
this->gender = gender;
}

QString human::get_gender()
{
return gender;
}

void human::set_date_of_birth(QString date_of_birth)
{
this->date_of_birth = date_of_birth;
}

QString human::get_date_of_birth()
{
return date_of_birth;
}

#ifndef HUMAN_H
#define HUMAN_H
#include <QString>

class human
{
protected:
int id;
QString surname;
QString name;
QString patronymic; // отчество
QString gender;
QString date_of_birth;
public:
    human();
    void set_id(int id);
    int get_id();
    void set_surname(QString surname);
    QString get_surname();
    void set_name(QString name);
    QString get_name();
    void set_patronymic(QString patronymic);
    QString get_patronymic();
    void set_gender(QString gender);
    QString get_gender();
    void set_date_of_birth(QString date_of_birth);
    QString get_date_of_birth();

};

#endif // HUMAN_H

#ifndef DOCTOR_ACC_H
#define DOCTOR_ACC_H
#include <QString>
#include "human.h"
class doctor_acc : public human
{
    QString login;
    QString password;
    QString position; //должность
public:
    doctor_acc();
    void set_login(QString login);
    void set_password(QString password);
    QString get_login();
    QString get_password();
    void set_position(QString position);
    QString get_position();
};

#endif // DOCTOR_ACC_H

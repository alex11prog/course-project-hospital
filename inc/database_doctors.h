#ifndef DATABASE_DOCTORS_H
#define DATABASE_DOCTORS_H
#include "doctor_acc.h"
#include <QVector>

class database_doctors
{
    int now_user_id; // id врача вошедшего в систему
    int last_doctor_id;     // id последнего добавленного врача
    const int num_column_admin_table = 9; //
    bool root;
public:
    int get_num_column_admin_table();
    void set_last_doctor_id(int last_id);
    void last_doctor_id_INC();
    int get_last_id();
    void set_now_user_id(int id);
    int get_now_user_id();
    bool check_root();// геттер проверки наличия прав админа
    void set_root(bool root);
    database_doctors();
    QVector<doctor_acc> vector_data_doctors;
};
extern database_doctors db_doctors;
#endif // DATABASE_DOCTORS_H

#include "inc/database_doctors.h"

int database_doctors::get_num_column_admin_table()
{
    return num_column_admin_table;
}

void database_doctors::set_last_doctor_id(int last_id)
{
    this->last_doctor_id = last_id;
}

void database_doctors::last_doctor_id_INC()
{
    last_doctor_id++;
}

int database_doctors::get_last_id()
{
    return last_doctor_id;
}

void database_doctors::set_now_user_id(int id)
{
this->now_user_id = id;
}

int database_doctors::get_now_user_id()
{
    return now_user_id;
}

bool database_doctors::check_root()
{
return root;
}

void database_doctors::set_root(bool root)
{
this->root = root;
}

database_doctors::database_doctors()
{
root = false;
}
database_doctors db_doctors;

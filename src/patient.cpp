#include "inc/patient.h"

void Patient::set_sick(bool sick)
{
this->sick = sick;
}

bool Patient::get_sick()
{
return sick;
}

void Patient::set_medic_id(int medic_id)
{
this->medic_id = medic_id;
}

int Patient::get_medic_id()
{
return medic_id;
}

void Patient::set_gender(int gender)
{
    this->gender = gender;
}

int Patient::get_gender()
{
    return gender;
}

void Patient::set_number_policy(QString number_policy)
{
this->number_policy = number_policy;
}

QString Patient::get_number_policy()
{
return number_policy;
}

void Patient::set_type_of_policy(int type_of_policy)
{
this->type_of_policy = type_of_policy;
}

int Patient::get_type_of_policy()
{
return type_of_policy;
}

void Patient::set_district(int district)
{
this->district = district;
}

int Patient::get_district()
{
return district;
}

Patient::Patient()
{
sick = false;
}

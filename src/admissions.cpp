#include "inc/admissions.h"

void Admissions::set_record_id(int record_id)
{
this->record_id = record_id;
}

int Admissions::get_record_id()
{
return record_id;
}

void Admissions::set_medic_id(int medic_id)
{
this->medic_id = medic_id;
}

int Admissions::get_medic_id()
{
return medic_id;
}

void Admissions::set_patient_id(int patient_id)
{
this->patient_id = patient_id;
}

int Admissions::get_patient_id()
{
return patient_id;
}

void Admissions::set_date_of_receipt(QString date_of_receipt)
{
this->date_of_receipt = date_of_receipt;
}

QString Admissions::get_date_of_receipt()
{
return date_of_receipt;
}

void Admissions::set_date_of_healing(QString date_of_healing)
{
this->date_of_healing = date_of_healing;
}

QString Admissions::get_date_of_healing()
{
return date_of_healing;
}

Admissions::Admissions()
{

}

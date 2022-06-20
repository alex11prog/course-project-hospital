#include "medical_record.h"

void medical_record::set_record_id(int record_id)
{
this->record_id = record_id;
}

int medical_record::get_record_id()
{
    return record_id;
}

void medical_record::set_medic_id(int medic_id)
{
    this->medic_id = medic_id;
}

int medical_record::get_medic_id()
{
    return medic_id;
}

void medical_record::set_patient_id(int patient_id)
{
    this->patient_id = patient_id;
}

int medical_record::get_patient_id()
{
    return patient_id;
}

void medical_record::set_name(QString name)
{
this->name = name;
}

QString medical_record::get_name()
{
return name;
}

void medical_record::set_date(QString date)
{
this->date = date;
}

QString medical_record::get_date()
{
return date;
}

medical_record::medical_record()
{

}

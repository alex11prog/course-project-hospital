#include "inc/database_patients.h"


void database_patients::set_active_patient_clicked_id(int id)
{
this->active_patient_clicked_id = id;
}

int database_patients::get_active_patient_clicked_id()
{
return active_patient_clicked_id;
}

void database_patients::last_patient_id_INC()
{
    last_patient_id++;
}

void database_patients::set_last_patient_id(int last_id)
{
    this->last_patient_id = last_id;
}

int database_patients::get_last_patient_id()
{
    return last_patient_id;
}

void database_patients::last_admission_id_INC()
{
    last_admission_id++;
}

void database_patients::set_last_admission_id(int last_id)
{
    this->last_admission_id = last_id;
}

int database_patients::get_last_admission_id()
{
    return last_admission_id;
}

void database_patients::last_analysis_id_INC()
{
    last_analysis_id++;
}

void database_patients::set_last_analysis_id(int last_id)
{
    this->last_analysis_id = last_id;
}

int database_patients::get_last_analysis_id()
{
    return last_analysis_id;
}

void database_patients::last_diagnosis_id_INC()
{
    last_diagnosis_id++;
}

void database_patients::set_last_diagnosis_id(int last_id)
{
    this->last_diagnosis_id = last_id;
}

int database_patients::get_last_diagnosis_id()
{
    return last_diagnosis_id;
}

void database_patients::last_operation_id_INC()
{
    last_operation_id++;
}

void database_patients::set_last_operation_id(int last_id)
{
    this->last_operation_id = last_id;
}

int database_patients::get_last_operation_id()
{
    return last_operation_id;
}

void database_patients::set_flag_run_add_analysis(bool flag)
{
    this->flag_run_add_analysis = flag;
}

bool database_patients::get_flag_run_add_analysis()
{
    return flag_run_add_analysis;
}

void database_patients::set_flag_run_add_diagnosis(bool flag)
{
    this->flag_run_add_diagnosis = flag;
}

bool database_patients::get_flag_run_add_diagnosis()
{
    return flag_run_add_diagnosis;
}

void database_patients::set_flag_run_add_operation(bool flag)
{
    this->flag_run_add_operation = flag;
}

bool database_patients::get_flag_run_add_operation()
{
    return flag_run_add_operation;
}

database_patients::database_patients()
{
    active_patient_clicked_id = 0;
    last_patient_id = 0;
    last_admission_id = 0;
    last_analysis_id = 0;
    last_diagnosis_id = 0;
    last_operation_id = 0;

    flag_run_add_analysis = false;
    flag_run_add_diagnosis = false;
    flag_run_add_operation = false;
}

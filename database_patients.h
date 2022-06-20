#ifndef DATABASE_PATIENTS_H
#define DATABASE_PATIENTS_H
#include <QVector>
#include "patient.h"

class database_patients
{
    int active_patient_clicked_id; // id выбранного пациента в данный момент
    int last_patient_id;     // id последнего добавленного пациента
    int last_admission_id;
    int last_analysis_id;
    int last_diagnosis_id;
    int last_operation_id;

    bool flag_run_add_analysis;
    bool flag_run_add_diagnosis;
    bool flag_run_add_operation;

public:
    const int num_rows_inform_table = 6; //
    const int num_column_admissions_table = 5;
    const int num_column_analyzes_table = 6;
    const int num_column_diagnoses_table = 8;
    const int num_column_operations_table = 8;
    const int num_column_statistics_table = 11;

    void set_active_patient_clicked_id(int id);
    int get_active_patient_clicked_id();
    void last_patient_id_INC();
    void set_last_patient_id(int last_id);
    int get_last_patient_id();
    void last_admission_id_INC();
    void set_last_admission_id(int last_id);
    int get_last_admission_id();
    void last_analysis_id_INC();
    void set_last_analysis_id(int last_id);
    int get_last_analysis_id();
    void last_diagnosis_id_INC();
    void set_last_diagnosis_id(int last_id);
    int get_last_diagnosis_id();
    void last_operation_id_INC();
    void set_last_operation_id(int last_id);
    int get_last_operation_id();
    void set_flag_run_add_analysis(bool flag);
    bool get_flag_run_add_analysis();
    void set_flag_run_add_diagnosis(bool flag);
    bool get_flag_run_add_diagnosis();
    void set_flag_run_add_operation(bool flag);
    bool get_flag_run_add_operation();

    database_patients();
    QVector<Patient> vector_data_patients;
};

#endif // DATABASE_PATIENTS_H

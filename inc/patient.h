#ifndef PATIENT_H
#define PATIENT_H
#include "human.h"
#include "admissions.h"
#include "analyzes.h"
#include "diagnosis.h"
#include "operations.h"
#include <QVector>

class Patient : public human
{
    bool sick;              // болеет
    int medic_id;
    int gender;             // 0 - муж , 1 - жен
    QString number_policy;  // номер полиса
    int type_of_policy;     // 0 (ОМС) или 1 (ВМП)
    int district;           // 0 - Адмиралтейский
                            // 1 - Василеостровский
                            // 2 - Выборгский
                            // 3 - Калининский
                            // 4 - Московский
                            // 5 - Петроградский
                            // 6 - Центральный
                            // 7 - Приморский
                            // 8 - Кировский
public:
    void set_sick(bool sick);
    bool get_sick();
    void set_medic_id(int medic_id);
    int get_medic_id();
    void set_gender(int gender);
    int get_gender();
    void set_number_policy(QString number_policy);
    QString get_number_policy();
    void set_type_of_policy(int type_of_policy);
    int get_type_of_policy();
    void set_district(int district);
    int get_district();

    QVector<Admissions> vector_admissions;
    QVector<Analyzes> vector_analyzes;
    QVector<Diagnosis> vector_diagnosis;
    QVector<Operations> vector_operations;
    Patient();
};

#endif // PATIENT_H

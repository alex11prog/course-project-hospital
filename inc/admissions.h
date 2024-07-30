#ifndef ADMISSIONS_H
#define ADMISSIONS_H
#include <QString>

class Admissions
{	int record_id;
    int medic_id;
    int patient_id;
    QString date_of_receipt; // дата поступления
    QString date_of_healing; // дата выписки
public:
    void set_record_id(int record_id);
    int get_record_id();
    void set_medic_id(int medic_id);
    int get_medic_id();
    void set_patient_id(int patient_id);
    int get_patient_id();
    void set_date_of_receipt(QString date_of_receipt);
    QString get_date_of_receipt();
    void set_date_of_healing(QString date_of_healing);
    QString get_date_of_healing();
    Admissions();
};

#endif // ADMISSIONS_H

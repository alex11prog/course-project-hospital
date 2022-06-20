#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H
#include <QString>

class medical_record
{
protected:
    int record_id;
    int medic_id;
    int patient_id;
    QString name;
    QString date;
public:
    void set_record_id(int record_id);
    int get_record_id();
    void set_medic_id(int medic_id);
    int get_medic_id();
    void set_patient_id(int patient_id);
    int get_patient_id();
    void set_name(QString name);
    QString get_name();
    void set_date(QString date);
    QString get_date();
    medical_record();
};

#endif // MEDICAL_RECORD_H

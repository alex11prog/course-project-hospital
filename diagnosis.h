#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H
#include <QString>
#include "analyzes.h"
class Diagnosis : public Analyzes
{
protected:
    QString complexity; // сложность
    QString duration; // продолжительность
public:
    void set_complexity(QString complexity);
    QString get_complexity();
    void set_duration(QString duration);
    QString get_duration();
    Diagnosis();
};

#endif // DIAGNOSIS_H

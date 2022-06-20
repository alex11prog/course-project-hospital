#ifndef ANALYZES_H
#define ANALYZES_H
#include <QString>
#include "medical_record.h"
class Analyzes : public medical_record
{
protected:
    QString result;
public:
    void set_result(QString result);
    QString get_result();
    Analyzes();
};

#endif // ANALYZES_H

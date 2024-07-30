#include "inc/diagnosis.h"

void Diagnosis::set_complexity(QString complexity)
{
this->complexity = complexity;
}

QString Diagnosis::get_complexity()
{
return complexity;
}

void Diagnosis::set_duration(QString duration)
{
this->duration = duration;
}

QString Diagnosis::get_duration()
{
return duration;
}

Diagnosis::Diagnosis()
{

}

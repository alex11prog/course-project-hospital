#ifndef CHECK_DATE_H
#define CHECK_DATE_H
#include <QDate>
#include <QString>
class Check_date
{
public:
    Check_date();
    bool check_format_date(QString date);
    bool check_exist_date(QString date);
};
extern Check_date check_date;
#endif // CHECK_DATE_H

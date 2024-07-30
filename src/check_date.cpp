#include "inc/check_date.h"

Check_date::Check_date()
{

}

bool Check_date::check_format_date(QString date)
{
    if(date.size() != 10) return false;
    QString s = date.number(date.at(0).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(1).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(2).unicode(), 10);
    if(s.toInt() != 46) return false;
    s = date.number(date.at(3).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(4).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(5).unicode(), 10);
    if(s.toInt() != 46) return false;
    s = date.number(date.at(6).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(7).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(8).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    s = date.number(date.at(9).unicode(), 10);
    if(s.toInt() < 48 || s.toInt() > 57) return false;
    return true;
}

bool Check_date::check_exist_date(QString date)
{
    QString day_str, month_str, year_str;
    day_str.push_back(date[0]);
    day_str.push_back(date[1]);
    month_str.push_back(date[3]);
    month_str.push_back(date[4]);
    year_str.push_back(date[6]);
    year_str.push_back(date[7]);
    year_str.push_back(date[8]);
    year_str.push_back(date[9]);
    int day = day_str.toInt();
    int month = month_str.toInt();
    int year = year_str.toInt();
    QDate d(year, month, day);
    return (d.isValid());
}
Check_date check_date;

#ifndef STATISTICS_H
#define STATISTICS_H
#include <QString>
#include <QVector>
class Statistics
{
    const static int num_district = 9;
public:
    void statistics_reset();
    Statistics();
    QString month;
    int arr_got_sick[num_district];
    int arr_recovered[num_district];
};

#endif // STATISTICS_H

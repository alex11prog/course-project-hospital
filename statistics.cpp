#include "statistics.h"

void Statistics::statistics_reset()
{
    for(int i = 0; i < num_district; i++){
        arr_got_sick[i] = 0;
        arr_recovered[i] = 0;
    }
}

Statistics::Statistics()
{
statistics_reset();
}

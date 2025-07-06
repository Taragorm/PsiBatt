/**
 * 
100	4.2
90	4.12
80	4.04
70	3.96
60	3.88
50	3.8
40	3.68
30	3.56
20	3.4
10	3.2
0	3.0                                                                      
 */

#include <stdint.h>

//-----------------------------------------------
/**
 * mV for capacity at 10% charge increments                                                                     
 */
static const uint16_t battmV_[] = {
    3000, // 0%
    3200, // 10
    3400, // 20
    3560, // 30
    3680, // 40
    3800, // 50
    3880, // 60
    3960, // 70
    4040, // 80
    4120, // 90
    4200  // 100%
};    
//-----------------------------------------------
int LiPoMvToPercent(uint16_t mv)
{
    if(mv<=battmV_[0])
        return 0;
        
    if(mv>=battmV_[10])
        return 10;
        
    //
    // find first ge
    // not worth a binary search for so few
    int grix=1;
    for(;battmV_[grix] < mv; ++grix)
        ;
        
    auto ub = battmV_[grix];
    if(ub==mv)
        return grix*10; // occasionally we will hit the table value
    
    auto lb = battmV_[grix-1];
    auto mvPerPercent = (ub-lb)/10; // as mv values are 0 in last place, nothing is lost
    auto mvresidue = mv - lb;
    
    // to nearest percent is fine here
    auto ret = 
        (grix-1)*10
        + (mvresidue + mvresidue/2) / mvPerPercent
        ;

    if(ret>100)
        ret = 100;
    if(ret<0)
        ret = 0;
        
    return ret;
}
//-----------------------------------------------
    

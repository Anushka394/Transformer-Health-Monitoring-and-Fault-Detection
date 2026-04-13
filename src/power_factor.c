#include "power_factor.h"
float pf_conf(float pf) {
    if(pf > 0.95) return 95;
    else if(pf > 0.85) return 75;
    else return 50;
}
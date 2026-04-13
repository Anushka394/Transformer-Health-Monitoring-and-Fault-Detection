
#include "voltage.h"


float voltage_conf(float v) {
    if(v >= 10.5 && v <= 11.5) return 95;
    else if(v >= 10 && v <= 12) return 75;
    else return 40;
}
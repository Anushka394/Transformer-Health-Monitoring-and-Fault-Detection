
#include "current.h"


float current_conf(float c) {
    if(c < 70) return 95;
    else if(c < 90) return 70;
    else return 30;
}
#include "temperature.h"
float temp_conf(float t) {
    if(t < 60) return 95;
    else if(t < 80) return 70;
    else return 30;
}
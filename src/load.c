#include "load.h"
float load_conf(float load) {
    if(load < 70) return 95;
    else if(load < 90) return 70;
    else return 40;
}
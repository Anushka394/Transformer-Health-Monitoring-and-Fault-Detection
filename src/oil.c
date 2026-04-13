#include "oil.h"

float oil_conf(float level) {
    if(level > 70) return 95;
    else if(level > 50) return 70;
    else return 30;
}
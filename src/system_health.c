#include "system_health.h"

float system_health(float v, float c, float load, float pf,
                    float oil_t, float wind_t, float oil, float r) {

    return (0.1*v + 0.15*c + 0.15*load +
            0.1*pf + 0.15*oil_t +
            0.15*wind_t + 0.1*oil + 0.1*r);
}
#include <stdio.h>
#include "voltage.h"
#include "current.h"
#include "load.h"
#include "power_factor.h"
#include "temperature.h"
#include "oil.h"
#include "relay.h"
#include "system_health.h"

int main() {

    FILE *fp = fopen("D:/Projects/Health_monitoring/data/transformer_dataset_500.csv", "r");

    if(fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    float v, c, load, pf, oil_temp, wind_temp, oil_level;
    int relay;

    fscanf(fp, "%*[^\n]\n");

    while(fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%d",
        &v,&c,&load,&pf,&oil_temp,&wind_temp,&oil_level,&relay)==8)
    {
        float vc = voltage_conf(v);
        float cc = current_conf(c);
        float lc = load_conf(load);
        float pfc = pf_conf(pf);
        float otc = temp_conf(oil_temp);
        float wtc = temp_conf(wind_temp);
        float oc = oil_conf(oil_level);
        float rc = relay_conf(relay);

        float health = system_health(vc,cc,lc,pfc,otc,wtc,oc,rc);

        printf("%f %f %f %f %f %f %f %d %f\n",
            v,c,load,pf,oil_temp,wind_temp,oil_level,relay,health);

        // FAULTS
        if(load > 90)
            printf("FAULT: OVERLOAD\n");

        if(oil_temp > 90 || wind_temp > 100)
            printf("FAULT: OVERHEATING\n");

        if(oil_level < 50)
            printf("FAULT: LOW_OIL\n");

        if(relay == 0)
            printf("FAULT: RELAY_TRIP\n");
    }

    fclose(fp);
    return 0;
}
//gcc src\*.c -Iinclude -o run.exe -lm
//cd dashboard
//python dashboard.py
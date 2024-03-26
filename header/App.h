#ifndef DA_FIRSTPROJECT_APP_H
#define DA_FIRSTPROJECT_APP_H

#include "Graph.h"

class App{
private:
    Graph* g;
public:
    void init();
    void domain();
    void Basicmetrics();
    void ReliabilitySensitivity();
    void allOrSpecific();
    void allCitiesWaterQuantity();
    void SpecificCityWaterQuantity();
    void balanceLoad();
    void removeReservoir();
    void checkWaterDeficit();
    void removePipelines();
    void removePumpingStation();

};

#endif

#ifndef DA_FIRSTPROJECT_CITY_H
#define DA_FIRSTPROJECT_CITY_H

#include "Node.h"

enum cityEnum {C_ID, C_NAME, C_CODE};

class City : public Node{
private:
    uint32_t demand;
    uint32_t population;
    std::string name;
public:
    City(uint32_t id, uint32_t demand, uint32_t population, std::string& code, std::string& name);
    const std::string& getName() const;
    uint32_t getDemand() const;
    uint32_t getPopulation() const;
};

#endif

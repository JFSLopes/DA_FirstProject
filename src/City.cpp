#include "../header/City.h"

City::City(uint32_t id, double demand, uint32_t population, std::string& code, std::string& name) :
            Node(id, code), demand(demand), population(population), name(std::move(name)) {}

const std::string &City::getName() const {
    return name;
}

double City::getDemand() const {
    return demand;
}

uint32_t City::getPopulation() const {
    return population;
}


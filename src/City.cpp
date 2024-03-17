#include "../header/City.h"

City::City(uint32_t id, uint32_t demand, uint32_t population, std::string& code, std::string& name) :
            Node(id, code), demand(demand), population(population), name(std::move(name)) {}

const std::string &City::getName() const {
    return name;
}

uint32_t City::getDemand() const {
    return demand;
}

uint32_t City::getPopulation() const {
    return population;
}

#include "../header/Reservoir.h"

Reservoir::Reservoir(std::string &name, std::string &municipality, std::string &code, uint32_t id, double maxDelivery):
    name(std::move(name)), municipality(std::move(municipality)), Node(id, code), maxDelivery(maxDelivery) {}

const std::string &Reservoir::getName() const {
    return name;
}

double Reservoir::getMaxDelivery() const {
    return maxDelivery;
}

const std::string &Reservoir::getMunicipality() const {
    return municipality;
}

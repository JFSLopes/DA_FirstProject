#ifndef DA_FIRSTPROJECT_RESERVOIR_H
#define DA_FIRSTPROJECT_RESERVOIR_H

#include "Node.h"

enum reservoirEnum {R_ID, R_NAME, R_CODE};

class Reservoir : public Node{
private:
    std::string name;
    std::string municipality;
    double maxDelivery;
public:
    Reservoir(std::string& name, std::string& municipality, std::string& code, uint32_t id, double maxDelivery);
    const std::string& getName() const;
    const std::string& getMunicipality() const;
    double getMaxDelivery() const;
};

#endif

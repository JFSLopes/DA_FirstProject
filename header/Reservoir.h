#ifndef DA_FIRSTPROJECT_RESERVOIR_H
#define DA_FIRSTPROJECT_RESERVOIR_H

#include "Node.h"

enum reservoirEnum {R_ID, R_NAME, R_CODE};

class Reservoir : public Node{
private:
    std::string name;
    std::string municipality;
    uint32_t maxDelivery;
public:
    Reservoir(std::string& name, std::string& municipality, std::string& code, uint32_t id, uint32_t maxDelivery);
    const std::string& getName() const;
    const std::string& getMunicipality() const;
    uint32_t getMaxDelivery() const;
};

#endif

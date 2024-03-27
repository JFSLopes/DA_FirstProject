#ifndef DA_FIRSTPROJECT_RESERVOIR_H
#define DA_FIRSTPROJECT_RESERVOIR_H

#include "Node.h"

/**
 * @enum reservoirEnum
 * @brief Used to know by which value the reservoir is being looked for
 */
enum reservoirEnum {
    R_ID, /// If the ID is going to be used
    R_NAME, /// If the name is going to be used
    R_CODE /// If the code is going to be used
};

/**
 * @class Reservoir
 * @brief Allows to represent a reservoir
 *
 * Inherits from node, providing additional functionality related to reservoir representation.
 */
class Reservoir : public Node{
private:
    std::string name; /// Name of the water reservoir
    std::string municipality; /// Municipality where the water reservoir is located
    double maxDelivery; /// Maximum delivery of water reservoir in m3/sec
public:
    /**
     * @brief Reservoir constructor
     * @param name Name of the reservoir
     * @param municipality Municipality where the reservoir is located
     * @param code Code of the reservoir
     * @param id Id of the reservoir
     * @param maxDelivery Maximum delivery of water reservoir in m3/sec
     */
    Reservoir(std::string& name, std::string& municipality, std::string& code, uint32_t id, double maxDelivery);
    /**
     * @return Returns the reservoir name.
     */
    const std::string& getName() const;
    /**
     * @return Returns the municipality where the reservoir is located.
     */
    const std::string& getMunicipality() const;
    /**
     * @return Returns the maximum delivery of water of that reservoir.
     */
    double getMaxDelivery() const;
};

#endif

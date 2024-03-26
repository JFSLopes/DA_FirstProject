#ifndef DA_FIRSTPROJECT_CITY_H
#define DA_FIRSTPROJECT_CITY_H

#include "Node.h"
#include <ostream>

/**
 * @enum cityEnum
 * @brief Used to know by which value the city is being looked for
 */
enum cityEnum {
     C_ID /// If the ID is going to be used
    ,C_NAME /// If the name is going to be used
    ,C_CODE /// If the code is going to be used
};

/**
 * @class City
 * @brief Allows to represent a city
 *
 * Inherits from Node, providing additional functionality related to city representation.
 */
class City : public Node{
private:
    double demand; /// Value of the demand of the city
    uint32_t population; /// Number of the population
    std::string name; /// Name of the city
public:
    /**
     * @brief City constructor
     * @param id Id of the city
     * @param demand Value of the city demand of water
     * @param population Value of the population
     * @param code Code of the city
     * @param name Name of the city
     */
    City(uint32_t id, double demand, uint32_t population, std::string& code, std::string& name);
    /**
     * @return Returns the city name.
     */
    const std::string& getName() const;
    /**
     * @return Returns the city demand.
     */
    double getDemand() const;
    /**
     * @return Returns the city number of population.
     */
    uint32_t getPopulation() const;

};

#endif

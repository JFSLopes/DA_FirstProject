#ifndef DA_FIRSTPROJECT_STATION_H
#define DA_FIRSTPROJECT_STATION_H

#include "Node.h"

/**
 * @enum stationEnum
 * @brief Used to know by which value the station is being looked for
 */
enum stationEnum {
     S_ID /// If the ID is going to be used
    ,S_CODE /// If the code is going to be used
};

/**
 * @class Station
 * @brief Allows to represent a station
 *
 * Inherits from Node, providing additional functionality related to station representation.
 */
class Station : public Node{
public:
    /**
     * @brief Station constructor
     *
     * @param id Id of the station
     * @param code Code of the station
     */
    Station(uint32_t id, std::string& code);
};

#endif

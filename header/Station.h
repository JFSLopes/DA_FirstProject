#ifndef DA_FIRSTPROJECT_STATION_H
#define DA_FIRSTPROJECT_STATION_H

#include "Node.h"

enum stationEnum {S_ID, S_CODE};

class Station : public Node{
private:
public:
    Station(uint32_t id, std::string& code);
};

#endif

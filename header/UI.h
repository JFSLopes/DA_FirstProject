#ifndef DA_FIRSTPROJECT_UI_H
#define DA_FIRSTPROJECT_UI_H

#include <string>
#include <stdint.h>
#include <unordered_map>
#include "City.h"
#include "Graph.h"

std::string getNewPath();
std::string getNewFileName(const std::string& name);
char getYesNoAnswer();
void displayChooseDataSet(std::string& reservoirs, std::string& stations, std::string& cities, std::string& pipes, std::string& path);
void displayDomain();
uint32_t askNumber(uint32_t upperLimit);
std::pair<int,std::string> askCityCodeNameId();
std::pair<uint32_t , std::string> askReservoirCodeNameID();
void displayBasicMetrics();
void displayReliabilitySensitivity();
void displayAllOrSpecific();
void printCity(City* city, double water);
void displayMetrics(metrics m);
void printMap(std::unordered_map<std::string , std::set<std::pair<Edge*,double>>> &map);


#endif

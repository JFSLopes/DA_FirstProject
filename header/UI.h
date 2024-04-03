#ifndef DA_FIRSTPROJECT_UI_H
#define DA_FIRSTPROJECT_UI_H

#include <string>
#include <stdint.h>
#include <unordered_map>
#include "City.h"
#include "Graph.h"
/**
 * @return Returns a string with the path of a file
 */
std::string getNewPath();
/**
 *
 * @param name String used to name the file
 * @return Returns the name of the file
 */
std::string getNewFileName(const std::string& name);
/**
 * @brief Reads the answer from the user to a yes or no question and checks if it is valid
 *
 * @return Returns the character associated to the answer
 */
char getYesNoAnswer();
/**
 * @brief Checks if the data will be read from the default files or if the user wants the use another set of files
 *
 * @param reservoirs name of the file used to read the reservoirs, if the user choice was not to utilize the default
 * @param stations name of the file used to read the stations, if the user choice was not to utilize the default
 * @param cities name of the file used to read the cities, if the user choice was not to utilize the default
 * @param pipes name of the file used to read the pipes, if the user choice was not to utilize the default
 * @param path path of the folder that contains the files utilized on the reading process
 */
void displayChooseDataSet(std::string& reservoirs, std::string& stations, std::string& cities, std::string& pipes, std::string& path);
/**
 * @brief Display the functionalities available on the application
 */
void displayDomain();
/**
 * @brief Reads a number from the user and checks if it is invalid
 *
 * @param upperLimit maximum value that can be read
 * @return Returns the number that was insert by the user
 */
uint32_t askNumber(uint32_t upperLimit);
/**
 * @brief Reads the CODE, NAME or ID related to a city given by the user
 * @return Returns a pair in which the first element represents the choice made by the user and the second the input of the user
 */
std::pair<int,std::string> askCityCodeNameId();
/**
 * @brief Reads the CODE, NAME or ID related to a Reservoir given by the user
 * @return Returns a pair in which the first element represents the choice made by the user and the second the input of the user
 */
std::pair<uint32_t , std::string> askReservoirCodeNameID();
/**
 * @brief Display the functionalities available on the application related to the network basic metrics
 */
void displayBasicMetrics();
/**
 * @brief Display the functionalities available on the application related to the network reliability sensitivity
 */
void displayReliabilitySensitivity();
/**
 * @brief Asks the user if he wants to know about the water quantity that reaches all the cities or about a specific one
 */
void displayAllOrSpecific();
/**
 * @brief Prints the code of a city and the water that reaches that city
 * @param city Code of the city
 * @param water Quantity of water that reaches the city
 */
void printCity(City* city, double water);
/**
 * @brief Displays the metrics of the network
 * @param m Struct that holds the Average, Max Difference and the Variance of the network
 */
void displayMetrics(metrics m);
/**
 * @brief Displays the content of a given map
 * @param map map that will be printed
 */
void printMap(std::unordered_map<std::string , std::set<std::pair<Edge*,double>>> &map);

void pipelinesRemoved(std::vector<std::pair<std::string,std::string>> &pipelines);

std::string pumpingStationsRemoved();


#endif

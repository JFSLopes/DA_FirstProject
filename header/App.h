#ifndef DA_FIRSTPROJECT_APP_H
#define DA_FIRSTPROJECT_APP_H

#include "Graph.h"

class App{
private:
    Graph* g;
public:
    /**
     * @brief Allows the application to be initialized in right way
     */
    void init();
    /**
     * @brief Allows the user to choose between the functionalities available on the application
     */
    void domain();
    /**
     * @brief Allows the user to choose between the functionalities available on the application related to Basic metric of the network
     */
    void Basicmetrics();
    /**
     * @brief Allows the user to choose between the functionalities available on the application related to the reliability sensitivity of the network
     */
    void ReliabilitySensitivity();
    /**
     * @brief Allows the user to choose whether he wants to know about the water quantity that reaches all the cities or about a specific one
     */
    void allOrSpecific();
    /**
     * @brief Allows the user to see the water quantity that arrives to all the cities in a file
     */
    void allCitiesWaterQuantity();
    /**
     * @brief Allows the user to see the water quantity that arrives to a specific city
     */
    void SpecificCityWaterQuantity();
    /**
     * @brief Balances the load of the pipelines
     *
     * This method is used to make the load of network´s pipelines homogeneous
     */
    void balanceLoad();
    /**
     * @brief Allows the user to see the effects of the removal of a reservoir on the network
     */
    void removeReservoir();
    /**
     * @brief Allows the user to see the water deficit of cities that cannot achieve the demanded water quantity
     */
    void checkWaterDeficit();
    /**
     * @brief Allows the user to see the effects of the removal of a pipeline on the network
     */
    void removePipelines(std::vector<std::pair<std::string,std::string>> &pipelines);
    /**
     * @brief Allows the user to see the effects of the removal of a pumping station on the network
     */
    void removePumpingStation();

    void askPipelines(std::vector<std::pair<std::string,std::string>> &pipelines);

};

#endif

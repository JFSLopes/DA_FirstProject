#ifndef DA_FIRSTPROJECT_GRAPH_H
#define DA_FIRSTPROJECT_GRAPH_H

class Vertex;

#include <queue>
#include <set>
#include "FileParse.h"
#include "Vertex.h"
#include "Reservoir.h"
#include "City.h"
#include "Station.h"

/**
 * @struct metrics
 * @brief Used to store the metrics of the graph
 */
struct metrics {
    double avg; /// Stores the average of deficit in each pipe
    double variance; /// Stores the variance of deficit in each pipe
    double maxDiff; /// Stores the maximum deficit in a pipe
};
/**
 * @class Graph
 * @brief Stores information in a graph structure
 *
 * This class allows to store all types of nodes, in this case Pumping Station, Cities and Reservoir as well was
 * all the connections between the nodes
 */
class Graph{
private:
    std::vector<Vertex*> vertexSet; /// Vector tha holds all vertexes that belong to the graph

    /**
     * @brief Creates a super sink and super source
     *
     * This method creates and connected a super source and sink to the respective nodes.
     * It is used in the Max Flow algorithm.
     *
     * @param removedReservoir Default value is nullptr, in case is a valid value indicates a reservoir that is going to be removed from the network.
     */
    void createSuperSourceSink(Vertex* removedReservoir = nullptr);
    /**
     * @brief Removes the super source, super sink and all the connection they belong to.
     */
    void removeSuperSourceSink();
    /**
     * @brief Finds all paths between 2 vertexes
     *
     * This method uses a DFS search to find all paths between a source vertex and a destination vertex.
     *
     * @param s Source vertex
     * @param d Destination vertex
     * @param path Vector that stores the edges from the current path being analysed.
     * @param paths Vector that stores all the paths
     */
    void findAllPaths(Vertex* s, Vertex* d, std::vector<Edge *>& path, std::vector<std::vector<Edge *>>& paths) const;
    /**
     * @brief Returns the minimal deficit (capacity - current flow) of all edges that belong to a path.
     *
     * @param path Path being analysed
     * @return Returns the value of the deficit.
     */
    double minimalDiffCapacityFlow(std::vector<Edge*>& path) const;
    /**
     * @brief Increments the flow along a path.
     *
     * This method increments the flow by 'flow' on the path being analysed.
     *
     * @param path Path being analysed
     * @param flow Value of the flow to be incremented
     */
    void incrementFlow(std::vector<Edge*>& path, double flow);
    /**
     * @brief Finds how a city is affected after the removal of a reservoir.
     *
     * This method uses a simple approach to find how cities are affected after the removal of a reservoir.
     * If the income edges connecting the directly affected network are full or close to be full, then the water lost,
     * because the reservoir is out of service, cannot be replaced from another reservoir. In this case finding how
     * the cities were affected is simple, we just removed the flow coming from the directly affected network.
     *
     * @param allPaths Represents all paths from the removed reservoir to delivery sites.
     */
    void simplerAlgorithm(std::vector<std::vector<Edge*>>& allPaths);
    /**
     * @brief Performs a DFS
     *
     * @param v Vertex being analysed
     * @param subGraph Vector that stores all the visited vertexes
     */
    void DFSVisit(Vertex* v, std::vector<Vertex*>& subGraph);
    /**
     * @brief Perform a DFS using the income edges.
     *
     * @param v Vertex being analysed
     * @param subGraph Vector that stores all the visited vertexes
     */
    void DFSVisitReverse(Vertex* v, std::vector<Vertex*>& subGraph);

public:
    const std::vector<Vertex*> getVertexSet() const;
    /**
     * @brief Return if the income edges of the subgraph are full or close to.
     *
     * @param allPaths Represents the sub-graph being analysed.
     * @return True if all income edges are full or close to be or False if at least one is not full.
     */
    bool incomeEdgesFull(std::vector<std::vector<Edge*>>& allPaths) const;
    /**
     * @brief Finds all paths from a vertex to any delivery site.
     *
     * This method uses a DFS to find all paths from a source vertex to any delivery site that finds during the DFS.
     *
     * @param s Source vertex
     * @param path Vector that represents the path being analysed.
     * @param paths Vector used to store all paths.
     */
    void findAllPaths(Vertex *s, std::vector<Edge *> &path, std::vector<std::vector<Edge *>> &paths) const;
    /**
     * @brief Finds a city in the graph
     *
     * @param type Enum used to identify if the id, code or name will be used in the search
     * @param str String that holds the name or code of the city
     * @param id Holds the id of the city
     * @return Pointer to the city if it was found or nullptr otherwise
     */
    City* getCity(cityEnum type, std::string& str, uint32_t id) const;
    /**
     * @brief Finds a city in the graph
     *
     * @param type Enum used to identify if the id or code will be used in the search
     * @param str String that holds the code of the station
     * @param id Holds the id of the station
     * @return Pointer to the station if it was found or nullptr otherwise
     */
    Station* getStation(stationEnum type, std::string& str, uint32_t id) const;
    /**
     * @brief Finds a reservoir in the graph
     *
     * @param type Enum used to identify if the id, code or name will be used in the search
     * @param str String that holds the name or code of the reservoir
     * @param id Holds the id of the reservoir
     * @return Pointer to the reservoir if it was found or nullptr otherwise
     */
    Reservoir* getReservoir(reservoirEnum type, std::string& str, uint32_t id) const;
    /**
     * @brief Used to find a vertex on the graph
     *
     * @param code Identifies the code of the vertex being looked for
     * @return Returns a pointer to the vertex being looked for or nullptr otherwise
     */
    Vertex* findVertex(std::string& code) const;
    /**
     * @brief Adds a vertex to the graph
     * @param node Pointer to the vertex being added.
     */
    void addVertex(Vertex* node);
    /**
     * @brief Removes the vertex all all the connection it belonged to.
     * @param v Vertex being removed
     */
    void removeVertex(Vertex* v);
    /**
     * @brief Tries to find an augmenting path in the residual graph
     *
     * @param source Source vertex
     * @param sink Destination vertex
     * @param removed In case it's different from nullptr, identifies the vertex that no longer belongs to the graph
     * @return True if a augmenting path was found, false otherwise
     */
    bool findAugPath(Vertex* source, Vertex* sink, Vertex* removed = nullptr);
    bool findAugPathSubGraph(Vertex* source, Vertex* sink, std::vector<Vertex*>& subGraph);
    double minResAugPath(Vertex* source, Vertex* sink);
    void augmentFlowPath(Vertex* source, Vertex* sink, double f);
    double edmondsKarp();
    void edmondsKarpRemovePipeline(Edge* edge);
    void edmondsKarpRemoveReservoir(Vertex* reservoir);
    void edmondsKarpRemovePumpingStation(Vertex* pumpingStation);
    metrics calculateMetrics() const;
    std::set<std::pair<std::string, double>> checkWaterNeeds();

    void balanceLoad();

    void removeReservoir(Vertex* reservoir);
    void removePumpingStation(Vertex* pumpingStation);
};

#endif

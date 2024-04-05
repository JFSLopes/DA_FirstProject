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
    /// Stores the average of deficit in each pipe
    double avg;
    /// Stores the variance of deficit in each pipe
    double variance;
    /// Stores the maximum deficit in a pipee
    double maxDiff;
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
     * T(n) = O((V+E) x n), where n is the size of the path being copied to the vector containing all of them
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
    /**
     * @brief Returns the vertex set of the graph.
     *
     * @return Vertex set
     */
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
     * T(n) = O((V+E) x n), where n is the size of the path being copied to the vector containing all of them
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
     * @brief Removes the vertex all all the connection it belonged to
     * @param v Vertex being removed
     */
    void removeVertex(Vertex* v);
    /**
     * @brief Tries to find an augmenting path in the residual graph
     *
     * @param source Source vertex
     * @param sink Destination vertex
     * @param removed In case it's different from nullptr, identifies the vertex that no longer belongs to the graph
     * @return True if an augmenting path is found, false otherwise
     */
    bool findAugPath(Vertex* source, Vertex* sink, Vertex* removed = nullptr);
    /**
     * @brief Tries to find an augmenting path in the residual subgraph from the source to the sink vertex, using BFS (breadth-first search)
     * @param source Source vertex of the augmenting path
     * @param sink Destination vertex of the augmenting path
     * @param subGraph Subgraph in which the augmenting path is searched
     * @return True if an augmenting path is found, false otherwise
     */
    Vertex* findAugPathSubGraph(Vertex* source, Vertex* removed);
    /**
     * @brief Tries to find a minimal augmenting path in the residual graph
     * @param source Source vertex
     * @param sink Destination vertex
     * @return Returns the maximum flow that can be sent from the source vertex to the destination vertex through the path found
     * If no path is found, returns 0
     */
    double minResAugPath(Vertex* source, Vertex* sink);
    double minResAugPath1(Vertex* source, Vertex* sink);
    /**
     * @brief  Augments the flow along the augmenting path found in the residual network from the source vertex to destination vertex
     * The flow is increased by the amount f given in the arguments
     * @param source Source vertex
     * @param sink Destination vertex
     * @param f Amount to augment the flow along the path
     */
    void augmentFlowPath(Vertex* source, Vertex* sink, double f);
    void augmentFlowPath1(Vertex* source, Vertex* sink, double f);
    /**
     * @brief Implements the Edmonds-Karp algorithm to find the maximum flow in a flow network
     *
     * This is done by finding augmenting paths in the residual network and augmenting the flow along the paths
     * T(n) = O(VE^2)
     *
     * @return Returns the maximum flow in the flow network
     */
    double edmondsKarp();
    /**
     * @brief Removes a pipeline from the flow network and then implements the Edmonds-Karp algorithm to find the maximum flow without the specified pipeline
     * @param edges Edge that represents the pipeline to be removed
     */
    void edmondsKarpRemovePipeline(std::vector<Edge*> edges);
    /**
     * @brief Removes a pumping station from the flow network and then implements the Edmonds-Karp algorithm to find the maximum flow after the removal
     * @param pumpingStation Vertex that represents the pumping station to be removed
     */
    void edmondsKarpRemovePumpingStation(Vertex* pumpingStation);
    /**
     * @brief Calculates the basic metrics of the network such as the average, variance and maximum difference
     * @return Returns a struct containing the average, variance and maximum difference
     */
    metrics calculateMetrics() const;
    /**
     * @brief Used to verify if all the water reservoirs supply enough water to all its delivery sites
     *
     * Each pair has a string (that holds the ID of the city) and a double value (that represents the water deficit of that city)
     * T(n) = O(n)
     *
     * @return Returns a set of pairs, listing all the cities that can´t be supplied with the desired amount of water
     */
    std::set<std::pair<std::string, double>> checkWaterNeeds();

    /**
     * @brief This functions balances the load in the graph redistributing flow from edges that are more close to being full to alternative paths
     * It finds alternative paths with the same source and destination vertex and redistributes the flow accordingly
     */
    void balanceLoad();

    /**
     * @brief Allows to see how the delivery sites are affected when a reservoir is removed
     * @param reservoir Vertex that represents the reservoir to be removed
     */
    void removeReservoir(Vertex* reservoir);
    /**
     * @brief Allows to see if by temporarily removing a pumping station affects the delivery capacity to all the cities
     * @param pumpingStation Vertex that represents the pumping station to be removed
     */
    void removePumpingStation(Vertex* pumpingStation);
    /**
     * @brief Finds edges on the graph
     *
     * @param orig Origin vertex of the edge being looked for
     * @param dest Destination vertex of the edge being looked for
     * @return nullptr if not found or a pointer to the edge otherwise
     */
    Edge* findEdge(const std::string& orig, const std::string& dest);
};

#endif

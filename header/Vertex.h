#ifndef DA_FIRSTPROJECT_VERTEX_H
#define DA_FIRSTPROJECT_VERTEX_H

class Edge;

#include <vector>
#include "Edge.h"
#include "Node.h"

/**
 * @class Vertex
 * @brief Allows to represent the information of any vertex on the graph
 */

class Vertex{
private:
    Node* node; /// Node that represents the vertex
    std::vector<Edge*> adj; /// Represents the edges that have the vertex as origin
    std::vector<Edge*> incoming; /// Represents the edges that have the vertex as destination
    bool visited; /// Flag to check if the vertex has already been visited
    Edge* path; /// Pointer to an edge, that is included in an augmenting path, that goes through the vertex on Edmonds-Karp algorithm
public:
    double needing;
    double has;
    /**
     * @brief Vertex Constructor
     * @param node Pointer to the node associated with this vertex
     */
    Vertex(Node* node);

    /**
     * @return Returns the node that represents the vertex
     */
    Node* getNode() const;
    /**
     * @return Returns the edge that has the vertex as origin
     */
    std::vector<Edge*> getAdj() const;
    /**
     * @return Returns the edge that has the vertex as destination
     */
    std::vector<Edge*> getIncoming() const;
    /**
     * @return Returns a pointer to a edge included in an augmenting path
     */
    Edge* getPath() const;
    /**
     * @return Returns the edge with least capacity to carry water
     */
    Edge* edgeMoreFull() const;

    /**
     * @brief Checks if the vertex is visited
     * @return Returns whether the vertex is visited or not
     */
    bool isVisited() const;
    /**
     * @brief Allows to set the flag to true or false
     * @param visited boolean that represents if the vertex is visited or not
     */
    void setVisited(bool visited);
    /**
     * @brief Allows to set the path provided by the Edge
     * @param path Pointer to an edge
     */
    void setPath(Edge *path);

    /**
     * @brief Allows to add a edge with destination on the vertex and specified weight
     * @param d Represents the destination vertex of the edge
     * @param w Represents the weight of the Edge
     */
    void addEdge(Vertex* d, double w);
    /**
     * @return Returns the water remaining in the reservoir after delivery
     */
    double remainReservoirDelivery() const;
    /**
     * @return Returns the amount of water that arrives to a city
     */
    double cityAmountOfWater() const;

    /**
     * @brief Function that erases all the edges included either on the adjacency edges or in the incoming edges of an specific Vertex
     */
    void removeEdges();
    /**
     * @brief Allows to remove a edge that has the vertex as destination
     * @param target Vertex destination of the edge to be removed
     */
    void removeEdge(Vertex* target);

    /**
     * @brief Operator overload in order to compare vertices by the difference between the amount of water that arrives to that node and the demand of that node
     * @param other Vertex used on the comparison
     * @return Returns true whether a specific Vertex has a minor value of difference than the Vertex other, false otherwise
     */
    bool operator<(const Vertex other) const;
    /**
     * @return Returns true if the incoming edges are full, false otherwise
     */
    bool incomingFull() const;
};

#endif

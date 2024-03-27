#ifndef DA_FIRSTPROJECT_EDGE_H
#define DA_FIRSTPROJECT_EDGE_H

class Vertex;

#include "Vertex.h"
/**
 * @class Edge
 * @brief Allows to represent the information of any edge on the graph
 */

class Edge{
private:
    Vertex* dest; /// Represents the destination Vertex of the edge
    Vertex* orig; /// Represents the origin Vertex of the edge
    double weight; /// Represents the weight of the edge
    double flow; /// Represents the flow that goes through the edge
    bool removed; /// Flag used to indicate if the edge should be ignored
public:
    /**
     * @brief Edge Constructor
     * @param orig Origin Vertex of the edge
     * @param dest Destination Vertex of the edge
     * @param weight Weight of the edge
     */
    Edge(Vertex* orig, Vertex* dest, double weight);
    /**
     * @return Returns the destination Vertex of the Edge
     */
    Vertex* getDest() const;
    /**
     * @return Returns the Origin Vertex of the Edge
     */
    Vertex* getOrig() const;
    /**
     * @return Returns the weight of the Edge
     */
    double getWeight() const;
    /**
     * @return Returns the flow of the edge
     */
    double getFlow() const;
    /**
     * @return Returns the flag
     */
    bool getRemoved() const;
    /**
     * @brief Allows to set the flow of an edge
     * @param f flow of the edge
     */
    void setFlow(double f);
    /**
     * @brief Allows to set the removed flag
     * @param r boolean that represents if the edge should be ignored or not
     */
    void setRemoved(bool r);
};

#endif

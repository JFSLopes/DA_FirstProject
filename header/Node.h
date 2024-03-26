#ifndef DA_FIRSTPROJECT_NODE_H
#define DA_FIRSTPROJECT_NODE_H

#include <cstdint>
#include <string>

/**
 * @class Node
 * @brief Allows to represent the basic information of any node on the graph
 */
class Node{
private:
    uint32_t id; /// Represents the id of the node
    std::string code; /// Represents the code of the node
public:
    /**
     * @brief Node destructor
     */
    virtual ~Node();
    /**
     * @brief Node constructor
     * @param id Id of the node
     * @param code Code of the node
     */
    Node(uint32_t id, std::string& code);
    /**
     * @return Returns the node id
     */
    uint32_t getID() const;
    /**
     * @return Returns the node code
     */
    const std::string& getCode() const;
};

#endif

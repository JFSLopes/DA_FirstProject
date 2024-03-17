#ifndef DA_FIRSTPROJECT_NODE_H
#define DA_FIRSTPROJECT_NODE_H

#include <cstdint>
#include <string>

class Node{
private:
    uint32_t id;
    std::string code;
public:
    virtual ~Node();
    Node(uint32_t id, std::string& code);
    uint32_t getID() const;
    const std::string& getCode() const;
};

#endif

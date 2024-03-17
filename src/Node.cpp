#include "../header/Node.h"

Node::Node(uint32_t id, std::string &code) : id(id), code(std::move(code)) {}
Node::~Node() {}

uint32_t Node::getID() const {
    return id;
}

const std::string &Node::getCode() const {
    return code;
}
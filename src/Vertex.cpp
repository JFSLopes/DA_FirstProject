#include "../header/Vertex.h"

Vertex::Vertex(Node* node) : node(node), path(nullptr) {}

Node* Vertex::getNode() const {
    return node;
}
#ifndef DA_FIRSTPROJECT_VERTEX_H
#define DA_FIRSTPROJECT_VERTEX_H

#include <vector>
#include "Edge.h"
#include "Node.h"

class Vertex{
private:
    Node* node;
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    bool visited;
    Edge* path;
public:
    Vertex(Node* node);
    Node* getNode() const;
};

#endif

#include "../header/Vertex.h"

Vertex::Vertex(Node* node) : node(node), path(nullptr) {}

Node* Vertex::getNode() const {
    return node;
}

std::vector<Edge *> Vertex::getAdj() const {
    return adj;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::addEdge(Vertex* d, double w) {
    Edge* edge = new Edge(this, d, w);
    adj.push_back(edge);
    d->incoming.push_back(edge);
}

bool Vertex::isVisited() const{
    return this->visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

Edge* Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}
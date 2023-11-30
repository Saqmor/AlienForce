#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include  <stack>
#include <sstream>
#include <fstream>
#include <random>

class Graph {
private:

    struct element{
        bool used;
        float weight;
    };

    element* matrix;
    std::size_t n;

    std::size_t* dijkstra(std::size_t s) const;
    void start(float* d, std::size_t* p,std::size_t s) const;
    void relaxEdge(float* d, std::size_t* p,std::size_t u,std::size_t v) const;
    bool existOpen(bool* open)const;

    void addEdgesFromFile2(std::string);

public:
    Graph(std::size_t n);

    ~Graph();

    bool edgeExists(std::size_t from, std::size_t to) const;
    void addEdge(std::size_t from, std::size_t to,float);
    void remEdge(std::size_t from, std::size_t to);
    void addNumVertices();
    void addEdgesFromFile();
    
    void showAllEdges() const;
    std::vector<std::size_t> neighbors(std::size_t v) const;
    std::size_t order() const;
    float pesoAresta(std::size_t u,std::size_t v) const;
        
    std::size_t minimumDist(bool* open,float* d) const;
    std::vector<std::size_t> minWay(std::size_t u,std::size_t v) const;
    void printMinWay(std::size_t u,std::size_t v) const;
};
#endif
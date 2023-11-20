#pragma once
#include <vector>
#include <float.h>
#include <iostream>
#include <stack>

class Graph {
private:

  struct element{
  bool used;
  float weight;
  };

  element* matrix;
  std::size_t n;

public:
  Graph(std::size_t n);

  ~Graph();

  bool edge_exists(std::size_t from, std::size_t to) const;
  void add_edge(std::size_t from, std::size_t to,float);
  void rem_edge(std::size_t from, std::size_t to);

  std::vector<std::size_t> neighbors(std::size_t v) const;
  
  std::size_t order() const;
  float peso_aresta(std::size_t u,std::size_t v) const;

  //Dijkstra
  void start(float* d, std::size_t* p,std::size_t s) const;
  void relax(float* d, std::size_t* p,std::size_t u,std::size_t v) const;
  bool exist_open(bool* open)const;
  std::size_t minimum_dist(bool* open,float* d) const;
  std::size_t* dijkstra(std::size_t s) const;
  std::vector<std::size_t> min_way(std::size_t u,std::size_t v) const;
  void print_min_caminh(std::size_t u,std::size_t v) const;
};



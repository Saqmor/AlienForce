#include "graph.hpp"


Graph::Graph(std::size_t nvertices) {
  n = nvertices;
  matrix = new element[(n*(n+1))/2]{false,0};
}

Graph::~Graph() {
  delete[] matrix;
}

bool Graph::edge_exists(std::size_t u, std::size_t v) const {
  if (u < v){
    std::swap(u, v);
  }
  return matrix[u*(u+1)/2+v].used;
}

void Graph::add_edge(std::size_t u, std::size_t v,float w) {
   if (u < v){
    std::swap(u, v);
  }
  matrix[u*(u+1)/2+v].used = true;
  matrix[u*(u+1)/2+v].weight = w;
}

void Graph::rem_edge(std::size_t u, std::size_t v) {
  if (u < v){
    std::swap(u, v);
  }
  matrix[u*(u+1)/2+v].used = false;
}
  
std::vector<std::size_t> Graph::neighbors(std::size_t v) const {
  std::vector<std::size_t> neigh;
  for (std::size_t from = 0; from < n; ++from){
    if (edge_exists(from, v))
      neigh.push_back(from);
  }
  return neigh; 
}

std::size_t Graph::order() const {
  return n;
}

float Graph::peso_aresta(std::size_t u,std::size_t v)const{
  if (u < v){
    std::swap(u,v);
  }
  return matrix[u*(u+1)/2+v].weight;
}

void Graph::start(float* d, std::size_t* p,std::size_t s) const{
  for(std::size_t i=0; i<n;i++){
    d[i]=FLT_MAX/2;
    p[i]=10*n;
  }
  d[s]=0;
}

void Graph::relax(float* d, std::size_t* p,std::size_t u,std::size_t v) const{
  if(d[u]+ peso_aresta(u,v)<d[v]){
    d[v]=d[u]+ peso_aresta(u,v);
    p[v]=u;
  }
}

bool Graph::exist_open(bool* open)const{
  for(std::size_t i=0; i<n; i++){
    if(open[i])
      return true;
  }
  return false;
}

std::size_t Graph::minimum_dist(bool* open,float* d) const{
  std::size_t i,min;

  for(i=0; i<n; i++){
    if(open[i])
      break;
  }
  min=i;

  for(i=min+1; i<n; i++){
    if(open[i] && d[min]>d[i])
      min=i;
  }
  return min;
}

std::size_t* Graph::dijkstra(std::size_t s) const{
  float* d = new float[n];
  std::size_t* p = new std::size_t[n];
  bool* open = new bool[n];

  for(std::size_t i=0; i<n; i++){
    open[i]=true;
  }

  start(d,p,s);

  while(exist_open(open)){
    std::size_t u = minimum_dist(open,d);
    open[u]=false;

    for(std::size_t i: neighbors(u)){
      if(open[i]){
        relax(d,p,u,i);
      }
    }
  }
  return p; 
}


std::vector<std::size_t> Graph::min_way(std::size_t u,std::size_t v) const{
  
  auto p=dijkstra(u);
  std::stack<std::size_t> aux;
  std::vector<std::size_t> min_way;

  for(std::size_t i=v; i!=u; i=p[i]){
    aux.push(i);
  }

  min_way.push_back(u);
  while(!aux.empty()){
    min_way.push_back(aux.top());
    aux.pop();
  }
  return min_way;
}

void Graph::print_min_caminh(std::size_t u,std::size_t v) const{
  auto m = min_way(u,v);

    std::cout<<std::endl;
    for(std::size_t i=0; i<m.size();i++){
        std::cout<<m[i];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}
#include "Graph.h"

Graph::Graph(std::size_t nvertices) {
    n = nvertices;
    matrix = new element[(n*(n+1))/2]{false,0};
}

Graph::~Graph() {
    delete[] matrix;
}

bool Graph::edgeExists(std::size_t u, std::size_t v) const {
    if (u < v){
        std::swap(u, v);
    }
    return matrix[u*(u+1)/2+v].used;
}

void Graph::addEdge(std::size_t u, std::size_t v,float w) {
    if (u < v){
        std::swap(u, v);
    }
    matrix[u*(u+1)/2+v].used = true;
    matrix[u*(u+1)/2+v].weight = w;
}

void Graph::remEdge(std::size_t u, std::size_t v) {
    if (u < v){
        std::swap(u, v);
    }
    matrix[u*(u+1)/2+v].used = false;
}

std::vector<std::size_t> Graph::neighbors(std::size_t v) const {
    std::vector<std::size_t> neigh;
    for (std::size_t from = 0; from < n; ++from){
        if (edgeExists(from, v))
            neigh.push_back(from);
    }
    return neigh;
}

std::size_t Graph::order() const {
    return n;
}

float Graph::pesoAresta(std::size_t u,std::size_t v)const{
    if (u < v){
        std::swap(u,v);
    }
    return matrix[u*(u+1)/2+v].weight;
}

void Graph::start(float* d, std::size_t* p,std::size_t s) const{
    for(std::size_t i=0; i<n;i++){
        d[i]=std::numeric_limits<float>::max()/2;
        p[i]=10*n;
    }
    d[s]=0;
}

void Graph::relaxEdge(float* d, std::size_t* p,std::size_t u,std::size_t v) const{
    if(d[u]+ pesoAresta(u,v)<d[v]){
        d[v]=d[u]+ pesoAresta(u,v);
        p[v]=u;
    }
}

bool Graph::existOpen(bool* open)const{
    for(std::size_t i=0; i<n; i++){
        if(open[i])
            return true;
    }
    return false;
}

std::size_t Graph::minimumDist(bool* open,float* d) const{
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

    while(existOpen(open)){
        std::size_t u = minimumDist(open,d);
        open[u]=false;

        for(std::size_t i: neighbors(u)){
            if(open[i]){
                relaxEdge(d,p,u,i);
            }
        }
    }
    return p;
}


std::vector<std::size_t> Graph::minWay(std::size_t u,std::size_t v) const{

    auto p=dijkstra(u);
    std::stack<std::size_t> aux;
    std::vector<std::size_t> minWay;

    for(std::size_t i=v; i!=u; i=p[i]){
        aux.push(i);
    }

    minWay.push_back(u);
    while(!aux.empty()){
        minWay.push_back(aux.top());
        aux.pop();
    }
    return minWay;
}

void Graph::printMinWay(std::size_t u,std::size_t v) const{
    auto m = minWay(u,v);

    std::cout<<std::endl;
    for(std::size_t i=0; i<m.size();i++){
        std::cout<<m[i];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}

void Graph::addNumVertices() {
    std::cin >> n;
}

void Graph::addEdgesFromFile(){
    std::ifstream is;
    std::size_t u,v;
    float w;

    is.open("graph_input.txt");
    is>>w;
    while(is>>u>>v>>w)
        addEdge(u,v,w);
    is.close();
}


void Graph::addEdgesFromFile2(std::string name_file){
    std::ifstream is;
    std::size_t u,v;
    float w;

    is>>w;
    is.open(name_file);
    while(is>>u>>v>>w)
        addEdge(u,v,w);
    is.close();
}

void Graph::showAllEdges() const{
    std::size_t u,v;

    for(u=0; u<n; u++){
        for(v=u; v<n; v++){
            if(edgeExists(u,v)){
                std::cout<<u<<" "<<v<<" ";
                std::cout<<pesoAresta(u,v);
                std::cout<<std::endl;
            }
        }
    }
}
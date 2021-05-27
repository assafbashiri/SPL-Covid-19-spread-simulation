//
// Created by spl211 on 02/11/2020.
//
#include <Graph.h>
#include <vector>
using namespace std;

//empty constructor
Graph::Graph():
edges() , isInf() , neighbor(){}

//desructor
Graph::~Graph() {
    edges.clear();
    isInf.clear();
    neighbor.clear();
}

//default constructor
Graph::Graph(std::vector<std::vector<int>> matrix):
edges(matrix) , isInf() , neighbor(){//constructor
    this->edges = matrix;
    int size = edges.size();
    for (int i = 0 ; i < size ; i++ ){
        this->isInf.push_back(false);
        this->neighbor.push_back(0);
        int size1 = edges.size();
        for (int j = 0 ; j < size1 ; j++) {
            if (edges[i][j] == 1)
                neighbor[i]++;
        }
    }

}

//copy constructor
Graph::Graph(const Graph &other):edges() , isInf() , neighbor(){
    int size = other.edges.size();
    for (int i = 0; i < size; i++) {
        this->edges.push_back(other.edges[i]);
    }
    size = other.isInf.size();
    for (int i = 0; i < size ; i++) {
        isInf.push_back(other.isInf[i]);
    }
    size = other.neighbor.size();
    for (int i = 0; i < size ; i++) {
        neighbor.push_back(other.neighbor[i]);
    }
}

//move constructor
Graph::Graph(Graph &&other)
:edges() , isInf() , neighbor() {
    this->edges = other.edges;
    this->isInf = other.isInf;
    this->neighbor = other.neighbor;
    other.edges = {};
    other.isInf = {};
    other.neighbor = {};
}



//assignment operator
const Graph & Graph::operator=(const Graph &other) {
    int size = other.edges.size();
    for (int i = 0; i < size; i++) {
        this->edges.push_back(other.edges[i]);
    }
    size = other.isInf.size();
    for (int i = 0; i < size; i++) {
        this->isInf.push_back(other.isInf[i]);
    }
    size = other.neighbor.size();
    for (int i = 0; i < size; i++) {
        this->neighbor.push_back(other.neighbor[i]);
    }
    return *this;
}



//move assignment operator
const Graph & Graph::operator=(Graph &&other){
    this->edges=other.edges;
    this->isInf=other.isInf;
    this->neighbor=other.neighbor;
    other.edges = {};
    other.isInf = {};
    other.neighbor = {};
    return *this;
}

std::vector<std::vector<int>> Graph::getEdges()
{
    return  edges;
}

void Graph::removeEdge(int a, int b)
{
    if (edges[a][b] == 1) {
      edges[a][b] = 0;
      edges[b][a] = 0;
      neighbor[a]--;
      neighbor[b]--;
    }
}

Graph * Graph::clone() const
{
    return new Graph(*this);
}

void Graph::infectNode(int nodeInd)
{
    isInf[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd)
{
    if (isInf[nodeInd]) {
        return true;
    }
    return false;
}

std::vector<bool> Graph::getIsInf() {
    return isInf;
}

std::vector<int> Graph::getNeighbor() {
    return neighbor;
}

int Graph::numberOfNode() {
    return edges.size();
}

void Graph::disconnect(int nodeDis) {
    for(int i=0;i<numberOfNode();i=i+1){
        removeEdge(nodeDis,i);
    }
}

bool Graph::clean(int node) {
    for(int i=0;i<numberOfNode();i=i+1){
        if(edges[node][i]==1 && !isInfected(i))
            return false;
    }
    return true;
}

void Graph::setEdges(std::vector<std::vector<int>> &matrix) {
    edges = matrix;
}

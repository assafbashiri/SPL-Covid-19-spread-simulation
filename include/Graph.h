#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    virtual ~Graph();//destructor
    Graph(); //empty constructor
    Graph(std::vector<std::vector<int>> matrix); //default constructor
    Graph(const Graph &other);//copy constructor
    Graph( Graph&&other);//move constructor
    const Graph& operator=(const Graph& other);//assignment operator
    const Graph& operator=(Graph&& other);//move assignment operator
    Graph* clone()const;
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    std::vector<std::vector<int>> getEdges();
    void removeEdge(int a, int b);
    std::vector<int> getNeighbor();
    std::vector<bool> getIsInf();
    int numberOfNode();
    void disconnect (int nodeDis);
    bool clean (int node);
    void setEdges(std::vector<std::vector<int>> &matrix);
private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> isInf;
    std::vector<int> neighbor;


};

#endif

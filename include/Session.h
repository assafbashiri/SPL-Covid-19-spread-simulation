

#include <vector>
#include <string>
#include "Graph.h"
#include <iostream>
#include <queue>
#include "Tree.h"
#ifndef TREE_H_
#define TREE_H_




class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> queue;
public:
    int cycle;
    std::queue<int> getQ();
    std::vector<int> infectedButNotVirus;
    virtual ~Session();//destructor
    Session(); //empty constructor
    Session(const std::string& path);//default constructor
    Session(const Session &session);//copy constructor
    Session( Session &&other);//move constructor
    const Session& operator=(const Session& other);// assignment operator
    const Session& operator=(Session&& other);//move assignment operator
    Session* clone() const;
    void simulate();
    void addAgent(const Agent& agent);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    Graph& getGraph();
    std::vector<Agent*> getAgents ();
    bool clean();
    Tree* bfs(int nodeRoot);
    int getCycle()const;
};
#endif
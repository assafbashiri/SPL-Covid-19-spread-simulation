//
// Created by spl211 on 03/11/2020.
//
#include <iostream>
#include <fstream>
#include "Session.h"
#include "Graph.h"
#include "Tree.h"
#include "Agent.h"
#include "json.hpp"
#include "queue"
#include <list>

using namespace std;
using json = nlohmann::json;

//empty constructor
Session::Session()
:g() , treeType() , agents() , queue()  , cycle() , infectedButNotVirus(){}

//destructor
Session::~Session() {
    for(auto &agent:agents) {
            delete agent;
    }
    agents.clear();
    queue.empty();
}

//default construction
Session::Session(const std::string &path):
g() , treeType() , agents(vector<Agent*>() ) , queue() , cycle() , infectedButNotVirus(){
    cycle=0;
    ifstream i(path);
    nlohmann::json j;
    i >> j;

    std::vector<std::vector<int>> edges;
    g = Graph(j["graph"]);
    for(const auto &ad : j["graph"]) {
        edges.push_back(ad);
    }
    if(j["tree"]=="M")
        treeType=MaxRank;
    if(j["tree"]=="R")
        treeType=Root;
    if(j["tree"]=="C")
        treeType=Cycle;
    int size = edges.size();
    for(int i = 0 ; i < size ;i++)
        infectedButNotVirus.push_back(0);

    for(pair<std::string, int > p: j["agents"]) {
        if (p.first == "V") {
            int curr=p.second;
            agents.push_back(new Virus(curr));
            infectedButNotVirus[curr]=1;
        }
        else
            agents.push_back(new ContactTracer());
    }
}



//copy constructor
Session::Session(const Session &other):
g(other.g) , treeType() , agents() , queue() , cycle() ,  infectedButNotVirus(){
    int size = other.agents.size();
    for (int i = 0 ; i< size ; i++)
        agents.push_back(other.agents[i]);
    treeType=other.treeType;
    queue=other.queue;
    cycle=other.cycle;
    infectedButNotVirus=other.infectedButNotVirus;
}

//move constructor
Session::Session(Session &&other):
g() , treeType() , agents() , queue(other.queue) , cycle(), infectedButNotVirus(){
    g = other.g;
    int size = other.agents.size();
    for (int i = 0 ; i < size ; i++) {
        agents.push_back(other.agents[i]);
    }
}

//asignment operator
 const Session& Session:: operator=(const Session& other){
    if(this == &other){return *this;}
        g=other.g;
        treeType=other.treeType;
        queue=other.queue;
        cycle=other.cycle;
        int size = other.infectedButNotVirus.size();
    for (int i = 0; i < size ; i++) {
        this->infectedButNotVirus.push_back(infectedButNotVirus[i]);
    }
    return *this;
}

//move assigment operator
const Session & Session::operator=(Session &&other){
    if (this == &other)
        return *this;
    g = other.g;
    treeType = other.treeType;
    agents = other.agents;
    queue = other.queue;
    return *this;
}

Session* Session::clone() const {
    return new Session(*this);
}

void Session::simulate() {
    int iteration = agents.size();
    for (int i = 0; i < iteration; i = i + 1) {
        agents[i]->act( *this);
    }
    cycle++;
    while ( !clean()){
        iteration = agents.size();
        for (int i = 0; i < iteration ; i = i + 1) {
            agents[i]->act( *this);
        }
        cycle++;
    }
    list<int> infectedFinal;
    int size = g.getIsInf().size();
    for (int i = 0 ; i < size ; i++)
    {
        if (g.getIsInf()[i])
        {
            infectedFinal.push_back(i);
        }
    }
    nlohmann::json j;
    j["infected"]=infectedFinal;
    for (auto& elem : g.getEdges()){
        j["graph"].push_back(elem);
    }
    ofstream o("./output.json");
    o << j << endl;
}

void Session::addAgent(const Agent &agent)
{
    agents.push_back(agent.clone());
}

void Session::enqueueInfected(int x)
{
    queue.push(x);
}

int Session::dequeueInfected()
{
    int output=queue.front();
    queue.pop();
    return output;
}

TreeType Session::getTreeType() const
{
    return this->treeType;
}

Graph& Session::getGraph() {
    return g;
}

std::vector<Agent*> Session::getAgents() {
    return this->agents;
}

bool Session::clean() {

    for(int i = 0;i< g.numberOfNode();i=i+1){
        if(g.isInfected(i) || infectedButNotVirus[i]==1)
            if(!g.clean(i))
                  return false;

    }
    return true;
}

 int Session::getCycle() const{
     return cycle;
}

Tree* Session::bfs(int rootLabel)
{
    vector<std::vector<int>> edges = g.getEdges();
    std::queue<Tree*> allMyTree;
    vector<bool> visited(edges.size(),false);
    Tree* tree = Tree::createTree(*this,rootLabel);
    allMyTree.push(tree);
    visited[rootLabel]=true;
    while (!allMyTree.empty()) {
        Tree* v = allMyTree.front();
        allMyTree.pop();
        for (int i = 0; i < (int) edges.size(); i++) {
            if (edges[v->getNode()][i] == 1) {
                if (!visited[i]) {
                    Tree* currTree = Tree::createTree(*this,i);
                    allMyTree.push(currTree);
                    v->addChild1(currTree);
                    visited[i]=true;
                }
            }
        }
    }
    return tree;
}

std::queue<int> Session::getQ()
{
    return queue;
}

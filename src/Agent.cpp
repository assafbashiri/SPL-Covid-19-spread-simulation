
#include <Agent.h>
#include <Graph.h>
#include <Tree.h>
#include <vector>
using namespace std;


Agent::Agent()=default;//constructor
Agent::~Agent() =default;
ContactTracer::ContactTracer() {}
ContactTracer::~ContactTracer(){}
ContactTracer * ContactTracer::clone() const {
    return new ContactTracer(*this);
}
void ContactTracer::act(Session& session) {
    if (!session.getQ().empty()){
        int currV = session.dequeueInfected();
        Tree *tree =session.bfs(currV);
        int nodeDis = tree->traceTree();
        std::vector<std::vector<int>> edges = session.getGraph().getEdges();
        for (int i = 0; i < session.getGraph().numberOfNode(); i = i + 1) {
            if (edges[nodeDis][i] == 1) {
                edges[nodeDis][i] = 0;
                edges[i][nodeDis] = 0;
            }
        }
        session.getGraph().setEdges(edges);
        delete tree;
    }
}

////////new class
Virus::Virus(int nodeInd):nodeInd(nodeInd){}

Virus* Virus::clone() const
{
    return new Virus(*this);
}

Virus::Virus(const Virus &virus) : nodeInd(virus.nodeInd)
{}

void Virus::act(Session& session)
{
    if (!session.getGraph().isInfected(nodeInd)){
        session.getGraph().infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
        Graph g = session.getGraph();
        vector<std::vector<int>> edges = g.getEdges();
        int nextNode=-1;
        int nNode = g.numberOfNode();
        for (int i = 0; i < nNode && nextNode == -1; i++) {
            if (edges[nodeInd][i] == 1 && !g.isInfected(i) && session.infectedButNotVirus[i]==0) {
                nextNode = i;
            }
        }
        if (nextNode != -1) {
            auto *newVirus = new Virus(nextNode);
            session.addAgent(*newVirus);
            session.infectedButNotVirus[nextNode]=1;
            delete (newVirus);
        }
}


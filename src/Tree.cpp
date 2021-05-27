
//
// Created by spl211 on 30/10/2020.
//

#include "../include/Session.h"
#include <list>
#include "queue"

using namespace std;

//empty constructor
Tree::Tree()
:node() , children() {}

//destructor
Tree:: ~Tree()
{
clear();
}

void Tree::clear() {
    for (Tree *t:children)
        delete t;
    node = 0;
}

//default construction
Tree::Tree(int rootLabel) :node(rootLabel), children()
{
    node = rootLabel;
    children.clear();
}

//copy constructor
Tree::Tree(const Tree &other):node() , children()
{
    node = other.node;
    int size = other.children.size();
    for (int i = 0; i < size; i++) {
        children.push_back(other.children[i]->clone());
    }
}

//move constructor
Tree::Tree(Tree &&other):
node() , children(){
    if(this == &other) {}
    else {
        node = other.node;
        children = other.children;
        other.node = 0;
        other.children = {};
    }
}

//assignment operator
Tree & Tree::operator=(const Tree& other) {
    if (this != &other)
    {
        int size = other.children.size();
        for(int i=0;i<size;i++){
            children.push_back(other.children[i]);
        }
        node = other.node;
    }
    return *this;
}

//move assignment operator
Tree & Tree::operator=(Tree &&other){
    if(this == &other) {return *this;}
    node = other.node;
    children = other.children;
    other.node = 0;
    int size = other.children.size();
    for (int i = 0; i < size ; ++i) {
        delete other.children[i];
    }
    return *this;

}
void Tree::addChild(const Tree &child)
{
    Tree* copyChild = child.clone();
    children.push_back(copyChild);
}
void Tree::addChild1(Tree *child)
{
    children.push_back(child);
}

Tree * Tree:: createTree(const Session& session, int rootLabel)
{
    Tree* tree;
    TreeType type = session.getTreeType();
    if (type==Cycle)
    {

        tree= new CycleTree(rootLabel, session.cycle);
                return  tree;
    }
    else if (type==MaxRank)
    {
        tree= new MaxRankTree(rootLabel);
        return  tree;
    }
    if (type==Root)
    {
        tree= new RootTree(rootLabel);
        return  tree;
    }
    return nullptr;
}


vector<Tree*> Tree::getChildren()
{
    return this->children;
}
 int Tree:: getNode() {
    return node;
}

//class CycleTree:

//empty constructor
CycleTree::CycleTree(): currCycle() {}

//constructor
CycleTree::CycleTree(int rootLabel, int currCycle):Tree (rootLabel), currCycle(currCycle){
    this->currCycle = currCycle;
}

CycleTree * CycleTree::clone() const {
    return  new CycleTree(*this);
}
int CycleTree::traceTree()
{
    int cycle=0;
    Tree* curr(this);
    while (&curr->getChildren()[0] != nullptr && cycle!=currCycle)
    {
        curr = curr->getChildren()[0];
        cycle++;
    }
    return curr->getNode();
}

//empty constructor
MaxRankTree::MaxRankTree()=default;

// constructor
MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel){}

int MaxRankTree::maxRankChildren(Tree* tree) {
    int childRank=tree->getChildren().size();
    int node=tree->getNode();
    int size = getChildren().size();
    for (int i = 0 ; i < size ;i++){

        int size = tree->getChildren()[i]->getChildren().size();
        if (size > childRank){

            childRank=tree->getChildren()[i]->getChildren().size();
            node=tree->getChildren()[i]->getNode();
        }
    }
    return node;
}
MaxRankTree * MaxRankTree::clone() const {
    return (new MaxRankTree(*this));
}


int MaxRankTree::traceTree() {
    int max = this->getChildren().size();
    int output = this->getNode();
    list<Tree  *> allMyTrees;
    allMyTrees.push_back(this);
    Tree* curr;
    while (!allMyTrees.empty()) {
        curr = allMyTrees.front();
        allMyTrees.pop_front();
        std::vector<Tree*> childrens=curr->getChildren();
        int maxRankChild =childrens.size();
        int node = curr->getNode();
        Tree* currChild;
        int size1 = childrens.size();
        for (int i = 0; i < size1; i++) {
            currChild = childrens[i];
            allMyTrees.push_back(currChild);
            int size = currChild->getChildren().size();
            if(size > maxRankChild){
                maxRankChild=currChild->getChildren().size();
                node=currChild->getNode();
            }
        }
        if (maxRankChild>max){
            max=maxRankChild;
            output=node;
        }


    }


    return output;
}

//empty constructor
RootTree::RootTree()=default;

//constructor
RootTree::RootTree (int rootLabel):Tree() {
    this->node = rootLabel;
}

int RootTree::traceTree() {
    return this->getNode();
}


RootTree * RootTree::clone() const{
    return (new RootTree());
}




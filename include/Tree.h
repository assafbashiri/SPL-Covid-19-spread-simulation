//
// Created by spl211 on 08/11/2020.
//

#ifndef SPL211_TREE_H
#define SPL211_TREE_H


#include <iostream>
#include <vector>


class Session;
class CycleTree;
class Tree{
protected:
    int node;
    std::vector<Tree*> children;
public:
    Tree(); // empty
    virtual ~ Tree();//destructor
    Tree(const Tree & other);//copy constructor
    Tree(Tree&& other);//move constructor
    Tree& operator=(const Tree& other) ;// assignment constructor
    Tree & operator=(Tree &&other);//move assigment
    Tree(int rootLabel);//default constructor
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    std::vector<Tree*> getChildren();
    int getNode();
    void addChild1( Tree *child);
    virtual Tree* clone() const=0;
    void clear();
};

class CycleTree: public Tree{
public:
    CycleTree();//empty constructor
    CycleTree(int rootLabel, int currCycle);//default constructor
    virtual int traceTree();
    virtual CycleTree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree();//empty constructor
    MaxRankTree(int rootLabel);//default constructor
    virtual int traceTree();
    int maxRankChildren (Tree* tree);
    virtual MaxRankTree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree();//empty constructor
    RootTree(int rootLabel);//default constructor
    virtual int traceTree();
    RootTree* clone() const;
};

#endif //SPL211_TREE_H
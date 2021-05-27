
#include <vector>
#include "Session.h"
#ifndef SESSION_H_
#define SESSION_H_
class Agent{
public:


    Agent();//empty constructor
    virtual void act(Session& session)=0;
    virtual Agent * clone() const=0;
    virtual ~Agent();
};

class ContactTracer: public Agent {
public:
    virtual ~ContactTracer();
    ContactTracer();
    virtual ContactTracer * clone() const;
    virtual void act( Session& session);
};

class Virus: public Agent{
private:
    const int nodeInd;
public:
    Virus(int nodeInd);
    Virus(const Virus &virus);
    virtual Virus * clone() const;
    virtual void act( Session& session);
};

#endif
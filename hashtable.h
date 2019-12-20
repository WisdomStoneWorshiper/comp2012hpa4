#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "vertex.h"
#include <list>

class Hashtable
{
public:
    Hashtable();
    void insertVertex(Vertex*);
    void removeVertex(Vertex*);
    bool containVertex(Vertex*);
    Vertex * getVertex(const int &);
private:
    list <Vertex*> table[50];
    const int HASHKEY=15973;
};

#endif // HASHTABLE_H

#ifndef MANAGER_H
#define MANAGER_H

#include "vertex.h"
#include "edge.h"
#include <list>
#include <vector>
#include "hashtable.h"
#include "avl.h"

class Manager
{
public:
    Manager();
    ~Manager();
    //std::vector<Vertex*>& getVlist();
    void addVertex(Vertex*);
    void deleteVertex(int);
    void addEdge(Edge*);
    void moveEdge(Vertex *);
    void connectVertex(std::list<Vertex*> & );
    void deleteEdge(Edge*);
    void startDijkstra(Vertex*);
    void showPath(Vertex*);
public slots:

private:
    std::vector<list<Vertex*>> v_list;
    std::vector<Edge*> e_list;
    std::vector<list<Vertex*>> result;
   // QWidget * mainWin;
};

#endif // MANAGER_H

#ifndef MANAGER_H
#define MANAGER_H

#include "vertex.h"
#include "edge.h"
#include <list>
#include <vector>
#include "hashtable.h"
#include "avl.h"
#include <QMessageBox>

class Manager
{
public:
    Manager();
    ~Manager();
    //std::vector<Vertex*>& getVlist();
    void addVertex(Vertex*);
    void deleteVertex(Vertex*);
    void addEdge(Edge*);
    void moveEdge(Vertex *);
    void connectVertex(std::list<Vertex*> & );
    void deleteEdge(Edge*);
    void startDijkstra(Vertex*);
    void showPath(Vertex*);
    void resetAllEdgeColor();
    void clearResult();
    bool isLocked();
private:
    std::vector<list<Vertex*>> v_list;
    std::vector<Edge*> e_list;
    std::vector<list<Vertex*>> result;
    bool locked;
   // QWidget * mainWin;
};

#endif // MANAGER_H

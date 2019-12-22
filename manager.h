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
    void addVertex(Vertex *);
    void deleteVertex(Vertex *);
    void addEdge(Edge *);
    void moveEdge(Vertex *);
    void connectVertex(std::list<Vertex *> &);
    void deleteEdge(Edge *);
    void startDijkstra(Vertex *);
    void showPath(Vertex *);
    void resetAllEdgeColor();
    void clearResult();
    bool isLocked();
    bool edgeExist(Vertex *, Vertex *);
    bool checkEmpty();
    Vertex *getVertex(const int &);
    int step();

private:
    std::vector<list<Vertex *>> v_list;
    std::vector<Edge *> e_list;
    std::vector<list<Vertex *>> result;
    bool locked, finishedAllStep;

    Hashtable *unvisitVertexTable;
    AVL *shortestDistanceAVL;
    Vertex *startPoint;
    Vertex *lastNeighbor;
    Vertex *current;
    Edge *lastEdge;
    vector<list<Vertex *>>::iterator currentVertexNeighborList;
    list<Vertex *>::iterator neighborVertex;
};

#endif // MANAGER_H

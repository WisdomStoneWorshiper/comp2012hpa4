#include "manager.h"

Manager::Manager()
{
    locked = false;
    finishedAllStep = false;
    unvisitVertexTable = nullptr;
    shortestDistanceAVL = nullptr;
    startPoint = nullptr;
    lastNeighbor = nullptr;
    current = nullptr;
    lastEdge = nullptr;
}

Manager::~Manager()
{
    for (int j = 0; j < e_list.size(); ++j)
    {
        delete e_list[j];
    }
    e_list.clear();
    for (int i = 0; i < v_list.size(); ++i)
    {
        Vertex *target = v_list[i].front();
        delete v_list[i].front();
        target = nullptr;
    }
    v_list.clear();
}

void Manager::deleteVertex(Vertex *target)
{
    vector<list<Vertex *>>::iterator targetList = find_if(v_list.begin(), v_list.end(),
                                                          [&](const list<Vertex *> v) { return v.front() == target; });
    if (targetList->front() != targetList->back())
    {
        for (int i = 0; i < e_list.size(); ++i)
        {
            if (e_list[i]->contains(targetList->front()))
            {
                deleteEdge(e_list[i]);
                delete e_list[i];
            }
        }
    }
    v_list.erase(targetList);
}

void Manager::addVertex(Vertex *v)
{
    list<Vertex *> vl;
    vl.push_back(v);
    v_list.push_back(vl);
}

void Manager::connectVertex(std::list<Vertex *> &vertexList)
{
    vector<list<Vertex *>>::iterator p1 = find_if(v_list.begin(), v_list.end(),
                                                  [&](const list<Vertex *> v) { return v.front() == vertexList.front(); });
    p1->push_back(vertexList.back());
    vector<list<Vertex *>>::iterator p2 = find_if(v_list.begin(), v_list.end(),
                                                  [&](const list<Vertex *> v) { return v.front() == vertexList.back(); });
    p2->push_back(vertexList.front());
}

void Manager::addEdge(Edge *e)
{
    e_list.push_back(e);
}

void Manager::deleteEdge(Edge *target)
{
    target->setVisible(false);
    vector<list<Vertex *>>::iterator p1 = find_if(v_list.begin(), v_list.end(),
                                                  [&](list<Vertex *> v) { return v.front()->getId() == target->getFirstPoint()->getId(); });
    p1->remove(target->getSecondPoint());
    vector<list<Vertex *>>::iterator p2 = find_if(v_list.begin(), v_list.end(),
                                                  [&](list<Vertex *> v) { return v.front()->getId() == target->getSecondPoint()->getId(); });
    p2->remove(target->getFirstPoint());
    vector<Edge *>::iterator targetPos = find(e_list.begin(), e_list.end(), target);
    e_list.erase(targetPos);
}

void Manager::startDijkstra(Vertex *startPoint)
{
    vector<list<Vertex *>>::iterator target = find_if(v_list.begin(), v_list.end(),
                                                      [&](list<Vertex *> t) { return t.front() == startPoint; });
    if (target->front() == target->back())
    {
        QMessageBox msg;
        msg.setText("No Path exists");
        msg.exec();
        return;
    }
    if (locked)
        return;
    else
        locked = true;
    finishedAllStep = false;
    unvisitVertexTable = {new Hashtable()};
    for (int i = 0; i < v_list.size(); ++i)
    {
        unvisitVertexTable->insertVertex(v_list[i].front());
        list<Vertex *> temp;
        temp.push_back(v_list[i].front());
        result.push_back(temp);
    }
    startPoint->setDistance(0);
    startPoint->repaint();
    shortestDistanceAVL = new AVL;
    shortestDistanceAVL->insert(startPoint, 0);
    startPoint->turnBlue();
    this->startPoint = startPoint;
}

void Manager::showPath(Vertex *target)
{

    vector<list<Vertex *>>::iterator resultListVectorPointer = find_if(result.begin(), result.end(),
                                                                       [&](list<Vertex *> temp) { return temp.front() == target; });

    if (resultListVectorPointer->front() == resultListVectorPointer->back())
        return;

    vector<Edge *>::iterator targetEdge = find_if(e_list.begin(), e_list.end(),
                                                  [&](Edge *e) { return (e->contains(resultListVectorPointer->front()) && e->contains(resultListVectorPointer->back())); });

    if (targetEdge != e_list.end())
        (*targetEdge)->turnBlue();

    showPath(resultListVectorPointer->back());
}

void Manager::resetAllEdgeColor()
{
    for (int i = 0; i < e_list.size(); ++i)
    {
        e_list[i]->resetColor();
    }
}

void Manager::clearResult()
{
    locked = false;
    resetAllEdgeColor();
    for (int i = 0; i < result.size(); ++i)
    {
        result[i].front()->setDistance(-1);
        result[i].front()->showTentativeDistance();
        result[i].front()->turnBlack();
        result[i].clear();
    }
    result.clear();
}

bool Manager::isLocked()
{
    return locked;
}

bool Manager::edgeExist(Vertex *v1, Vertex *v2)
{
    for (int i = 0; i < e_list.size(); ++i)
    {
        if (e_list[i]->contains(v1) && e_list[i]->contains(v2))
            return true;
    }
    return false;
}

Vertex *Manager::getVertex(const int &pos)
{
    return v_list[pos].front();
}

int Manager::step()
{
    if (finishedAllStep)
        return 0;
    static int state = 0;
    switch (state)
    {
    case 0:
        if (!shortestDistanceAVL->is_empty())
        {
            lastNeighbor = nullptr;
            if (current != nullptr)
                current->turnGrey();
            current = shortestDistanceAVL->removeShortest();
            if (!unvisitVertexTable->containVertex(current))
            {
                return 1;
            }
            else
                unvisitVertexTable->removeVertex(current);

            current->turnBlue();
        }
        else
        {
            current->turnGrey();
            delete unvisitVertexTable;
            delete shortestDistanceAVL;
            unvisitVertexTable = nullptr;
            shortestDistanceAVL = nullptr;
            QMessageBox msg;
            msg.setText("The algorithm finished");
            msg.exec();
            state = 0;
            finishedAllStep = true;
            return 0;
        }
        currentVertexNeighborList = find_if(v_list.begin(), v_list.end(),
                                            [&](list<Vertex *> temp) { return temp.front() == current; });
        neighborVertex = currentVertexNeighborList->begin();
        state = 1;
        if (current == startPoint)
            return 1;
        break;
    case 1:
        if (lastEdge != nullptr)
            lastEdge->resetColor();
        if (lastNeighbor != nullptr)
            lastNeighbor->turnCyan();
        if (++neighborVertex != currentVertexNeighborList->end())
        {
            if (!unvisitVertexTable->containVertex(*neighborVertex))
            {
                return 1;
            }
            lastEdge = *find_if(e_list.begin(), e_list.end(),
                                [&](Edge *e) { return e->contains(current) && e->contains(*neighborVertex); });

            lastEdge->turnBlue();
            int d = lastEdge->getDistance() + current->getDistance();
            if (d < (*neighborVertex)->getDistance() || (*neighborVertex)->getDistance() == -1)
            {
                (*neighborVertex)->setDistance(d);
                shortestDistanceAVL->insert(*neighborVertex, (*neighborVertex)->getDistance());
                vector<list<Vertex *>>::iterator q = find_if(result.begin(), result.end(),
                                                             [&](list<Vertex *> temp) { return temp.front() == *neighborVertex; });
                if (startPoint == q->front())
                {
                    return 1;
                }
                else if (q->back() == q->front())
                    q->push_back(current);
                else
                {
                    q->pop_back();
                    q->push_back(current);
                }
                (*neighborVertex)->turnGreen();
                lastNeighbor = *neighborVertex;
            }
            else
            {
                (*neighborVertex)->turnRed();
            }
            lastNeighbor = *neighborVertex;
            (*neighborVertex)->repaint();
        }
        else
        {
            state = 0;
            return 1;
        }
    }
    return -1;
}

bool Manager::checkEmpty()
{
    return v_list.size() == 0;
}

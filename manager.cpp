#include "manager.h"

Manager::Manager()
{
    locked=false;
}

Manager::~Manager(){
    for (int j=0;j<e_list.size();++j){
        delete e_list[j];
    }
    e_list.clear();
    for(int i=0;i<v_list.size();++i){
            Vertex* target=v_list[i].front();
            delete v_list[i].front();
            target=nullptr;
    }
    v_list.clear();
}


void Manager::deleteVertex(Vertex* target){
    vector<list<Vertex*>>::iterator targetList=find_if(v_list.begin(),v_list.end(),
                                                     [&](const list<Vertex*> v){return v.front()==target;});
    if (targetList->front()!=targetList->back()){
    for (int i=0;i<e_list.size();++i){
        if (e_list[i]->contains(targetList->front())){
            deleteEdge(e_list[i]);
            delete e_list[i];
        }
    }
    }
    v_list.erase(targetList);
}

void Manager::addVertex(Vertex* v){
    list<Vertex*>vl;
    vl.push_back(v);
    v_list.push_back(vl);
}

void Manager::connectVertex(std::list<Vertex*> & vv){
    vector<list<Vertex*>>::iterator p1=find_if(v_list.begin(),v_list.end(),
                                                     [&](const list<Vertex*> v){return v.front()==vv.front();});
    p1->push_back(vv.back());
    vector<list<Vertex*>>::iterator p2=find_if(v_list.begin(),v_list.end(),
                                                     [&](const list<Vertex*> v){return v.front()==vv.back();});
    p2->push_back(vv.front());
}

void Manager::addEdge(Edge* e){
    e_list.push_back(e);
}

void Manager::deleteEdge(Edge * target){
    target->setVisible(false);
    vector<list<Vertex*>>::iterator p1=find_if(v_list.begin(),v_list.end(),
                                                     [&](list<Vertex*> v){return v.front()->getId()==target->getFirstPoint()->getId();});
    p1->remove(target->getSecondPoint());
    vector<list<Vertex*>>::iterator p2=find_if(v_list.begin(),v_list.end(),
                                                     [&](list<Vertex*> v){return v.front()->getId()==target->getSecondPoint()->getId();});
    p2->remove(target->getFirstPoint());
    vector<Edge*>::iterator targetPos=find(e_list.begin(),e_list.end(),target);
    e_list.erase(targetPos);
}

void Manager::startDijkstra(Vertex *startPoint){
    vector<list<Vertex*>>::iterator target=find_if(v_list.begin(),v_list.end(),
                                    [&](list<Vertex*> t){return t.front()==startPoint;});
    if (target->front()==target->back()){
        QMessageBox msg;
        msg.setText("No Path exists");
        msg.exec();
        return;
    }
    if (locked)
        return;
    else
        locked=true;
    Hashtable* unvisitVertexTable{new Hashtable()};
    for (int i=0;i<v_list.size();++i){
        unvisitVertexTable->insertVertex(v_list[i].front());
        //qDebug()<<"hashloop"<<v_list[i].front()->getId();
        list<Vertex*>temp;
        temp.push_back(v_list[i].front());
        result.push_back(temp);
    }
    startPoint->setDistance(0);
    startPoint->repaint();
    //qDebug()<<"startp"<<startPoint->getId();
    AVL pq;
    pq.insert(startPoint,0);
    while(!pq.is_empty()){
        //pq.print();
        Vertex* current=pq.removeShortest();
        //qDebug()<<"After remove shortest";
        //pq.print();
        //qDebug()<<"currentId"<<current->getId();
        if (!unvisitVertexTable->containVertex(current)){
            //qDebug()<<pq.is_empty();
            continue;
        }else
            unvisitVertexTable->removeVertex(current);
        vector<list<Vertex*>>::iterator t=find_if(v_list.begin(),v_list.end(),
                                        [&](list<Vertex*> temp){return temp.front()==current;});
        for (list<Vertex*>::iterator i=++t->begin();i!=t->end();++i){

            if (!unvisitVertexTable->containVertex(*i)){
                //qDebug()<<(*i)->getId()<<unvisitVertexTable->containVertex(*i);
                continue;
            }
            vector<Edge*>::iterator ep=find_if(e_list.begin(),e_list.end(),
                          [&](Edge* e){return e->contains(current)&&e->contains(*i);});
            //qDebug()<<"current id:"<<current->getId()<<"dis:"<<current->getDistance()<<"neighbor id:"<<(*i)->getId()<<"edge:"<<(*ep)->getDistance();
            int d=(*ep)->getDistance()+current->getDistance();
            if (d<(*i)->getDistance() || (*i)->getDistance()==-1){
                (*i)->setDistance(d);
                //qDebug()<<"line108"<<(*i)->getId()<<(*i)->getDistance();
                pq.insert(*i,(*i)->getDistance());
                pq.print();
                vector<list<Vertex*>>::iterator q=find_if(result.begin(),result.end(),
                                                [&](list<Vertex*> temp){return temp.front()==*i;});
                if (startPoint==q->front()){
                    continue;
                }
                else if (q->back()==q->front())
                    q->push_back(current);
                else{
                    q->pop_back();
                    q->push_back(current);
                }
            }
            (*i)->repaint();
        }
        //qDebug()<<"finsih loop";
        pq.print();
    }
    delete unvisitVertexTable;
}

void Manager::showPath(Vertex * target){

    vector<list<Vertex*>>::iterator resultListVectorPointer=find_if(result.begin(),result.end(),
                                    [&](list<Vertex*> temp){return temp.front()==target;});

    if (resultListVectorPointer->front()==resultListVectorPointer->back())
        return;

    vector<Edge*>::iterator targetEdge=find_if(e_list.begin(),e_list.end(),
                                               [&](Edge* e){return (e->contains(resultListVectorPointer->front())&&e->contains(resultListVectorPointer->back()));});

    if (targetEdge!=e_list.end())
        (*targetEdge)->turnBlue();
    showPath(resultListVectorPointer->back());
}

void Manager::resetAllEdgeColor(){
    for (int i=0;i<e_list.size();++i){
        e_list[i]->resetColor();
    }
}

void Manager::clearResult(){
    locked=false;
    resetAllEdgeColor();
    for (int i=0;i<result.size();++i){
        result[i].front()->setDistance(-1);
        result[i].front()->showTentativeDistance();
        result[i].clear();
    }
    result.clear();
}

bool Manager::isLocked(){
    return locked;
}

bool Manager::edgeExist(Vertex* v1,Vertex* v2){
    for (int i=0;i<e_list.size();++i){
        if (e_list[i]->contains(v1) && e_list[i]->contains(v2))
            return true;
    }
    return false;
}

Vertex* Manager::getVertex(const int & pos){
    return v_list[pos].front();
}

//bool Manager::step(){
//    static int state=0;
//    switch(state){
//    case 0:
//        vector<list<Vertex*>>::iterator target=find_if(v_list.begin(),v_list.end(),
//                                        [&](list<Vertex*> t){return t.front()==startPoint;});
//        if (target->front()==target->back()){
//            QMessageBox msg;
//            msg.setText("No Path exists");
//            msg.exec();
//            return true;
//        }
//        if (locked)
//            return true;
//        else
//            locked=true;
//        Hashtable* unvisitVertexTable{new Hashtable()};
//        for (int i=0;i<v_list.size();++i){
//            unvisitVertexTable->insertVertex(v_list[i].front());
//            //qDebug()<<"hashloop"<<v_list[i].front()->getId();
//            list<Vertex*>temp;
//            temp.push_back(v_list[i].front());
//            result.push_back(temp);
//        }
//        startPoint->setDistance(0);
//        startPoint->repaint();
//        //qDebug()<<"startp"<<startPoint->getId();
//        AVL pq;
//        pq.insert(startPoint,0);
//    }
//}

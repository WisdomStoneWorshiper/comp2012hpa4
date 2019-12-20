#include "manager.h"
#include <QDebug>

Manager::Manager()
{

}

Manager::~Manager(){
    for (int j=0;j<e_list.size();++j){
        delete e_list[j];
    }
    e_list.clear();
    for(int i=0;i<v_list.size();++i){
        //QString l;
        for(list<Vertex*>::iterator j=v_list[i].begin();j!=v_list[i].end();++j){
            delete *j;
        }
        //qDebug()<<l;
    }
    v_list.clear();

}


void Manager::deleteVertex(int id){
    qDebug()<<"m2";
    vector<list<Vertex*>>::iterator targetList=find_if(v_list.begin(),v_list.end(),
                                                     [&](const list<Vertex*> v){return v.front()->getId()==id;});
    qDebug()<<"m1";
    if (targetList->front()!=targetList->back()){
        qDebug()<<"m3";
    for (int i=0;i<e_list.size();++i){
        qDebug()<<"m4";
        if (e_list[i]->contains(targetList->front())){
            qDebug()<<"m5";
            //e_list[i]->setVisible(false);
            deleteEdge(e_list[i]);
            delete e_list[i];
            qDebug()<<"m6";
        }
    }
    }
    qDebug()<<"m7";
    //Vertex*target=targetList->front();
    qDebug()<<"m8";
    v_list.erase(targetList);
    qDebug()<<"m9";
    //target->deleteLater();
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
    //target->deleteLater();
    qDebug()<<"m10";
}

void Manager::startDijkstra(Vertex *startPoint){

    Hashtable* unvisitVertexTable{new Hashtable()};
    for (int i=0;i<v_list.size();++i){
        unvisitVertexTable->insertVertex(v_list[i].front());
        qDebug()<<"hashloop"<<v_list[i].front()->getId();
        list<Vertex*>temp;
        temp.push_back(v_list[i].front());
        result.push_back(temp);
    }
    startPoint->setDistance(0);
    startPoint->repaint();
    qDebug()<<"startp"<<startPoint->getId();
    AVL pq;
    pq.insert(startPoint,0);
    while(!pq.is_empty()){

        Vertex* current=pq.removeShortest();
        qDebug()<<"currentId"<<current->getId();
        if (!unvisitVertexTable->containVertex(current))
            continue;
        else
            unvisitVertexTable->removeVertex(current);
        qDebug()<<"i am here";
        for(int i=0;i<v_list.size();++i){
            QString l;
            for(list<Vertex*>::iterator j=v_list[i].begin();j!=v_list[i].end();++j){
                l=l+" "+QString::number((*j)->getId());
            }
            qDebug()<<l;
        }
        vector<list<Vertex*>>::iterator t=find_if(v_list.begin(),v_list.end(),
                                        [&](list<Vertex*> temp){return temp.front()==current;});
        QString r;
        for (list<Vertex*>::iterator j=t->begin();j!=t->end();++j){
            r=r+" "+QString::number((*j)->getId());
        }
        qDebug()<<"line98"<<r;
        for (list<Vertex*>::iterator i=++t->begin();i!=t->end();++i){

            if (!unvisitVertexTable->containVertex(*i))
                continue;
            vector<Edge*>::iterator e=find_if(e_list.begin(),e_list.end(),
                          [&](Edge* e){return e->contains(current)&&e->contains(*i);});
            qDebug()<<"current"<<current->getId()<<"neighbor"<<(*i)->getId();
            int d=(*e)->getDistance();
            if (d<(*i)->getDistance() || (*i)->getDistance()==-1){
                (*i)->setDistance(current->getDistance()+d);
                qDebug()<<"line108"<<(*i)->getId()<<current->getDistance()+d;
                pq.insert(*i,(*i)->getDistance());
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


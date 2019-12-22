#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,m()
{
    ui->setupUi(this);
    //draw=false;
    ui->label->setStyleSheet("background-color:white;");
    ui->addVertexBtn->setCheckable(true);
    ui->addEdgeBtn->setCheckable(true);
    ui->startCalcalationBtn->setCheckable(true);
    ui->showPathBtn->setCheckable(true);
    ui->clearBtn->setEnabled(false);
    ui->showPathBtn->setEnabled(false);
    //connect(this,SIGNAL(ui->addVertexBtn->toggled(bool)),Vertex,SLOT(changeBtnState(bool)));
}

int Vertex::nextID=0;

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event){
    //draw=true;
    if (ui->addVertexBtn->isChecked()){
        addVertexAction(event->x(),event->y());
//    Vertex* v=new Vertex(event->x(), event->y(), ui->label);
//    //qDebug()<<event->x()<<event->y();
//    m.addVertex(v);
//    connect(v,SIGNAL(deleteAction(Vertex*, bool &)), this, SLOT(rightClickVertex(Vertex*, bool &)));
//    connect(ui->addEdgeBtn, SIGNAL(toggled(bool)),v, SLOT(catchEdgeBtnState(bool)));
//    connect(v,SIGNAL(addEdgeAction(Vertex *, const bool &)),this,SLOT(leftClickVertex(Vertex *, const bool &)));
//    connect(ui->startCalcalationBtn,SIGNAL(toggled(bool)),v,SLOT(catchStartBtnState(bool)));
//    connect(v,SIGNAL(startCalAction(Vertex*)),this,SLOT(startCalcalationAction(Vertex*)));
//    connect(v,SIGNAL(showP(Vertex*)),this,SLOT(showPathAction(Vertex*)));
//    connect(ui->showPathBtn,SIGNAL(toggled(bool)),v,SLOT(catchShowPathBtnState(bool)));
    }
}

void Widget::addVertexAction(const int & x, const int & y)
{
    Vertex* v=new Vertex(x, y, ui->label);
    m.addVertex(v);
    connect(v,SIGNAL(deleteAction(Vertex*, bool &)), this, SLOT(rightClickVertex(Vertex*, bool &)));
    connect(ui->addEdgeBtn, SIGNAL(toggled(bool)),v, SLOT(catchEdgeBtnState(bool)));
    connect(v,SIGNAL(addEdgeAction(Vertex *, const bool &)),this,SLOT(leftClickVertex(Vertex *, const bool &)));
    connect(ui->startCalcalationBtn,SIGNAL(toggled(bool)),v,SLOT(catchStartBtnState(bool)));
    connect(v,SIGNAL(startCalAction(Vertex*)),this,SLOT(startCalcalationAction(Vertex*)));
    connect(v,SIGNAL(showP(Vertex*)),this,SLOT(showPathAction(Vertex*)));
    connect(ui->showPathBtn,SIGNAL(toggled(bool)),v,SLOT(catchShowPathBtnState(bool)));
}
void Widget::on_addVertexBtn_toggled(bool checked)
{
    if (checked)
        ui->addEdgeBtn->setChecked(!checked);
}

void Widget::rightClickVertex(Vertex* target, bool & canDelete){
    canDelete=!m.isLocked();
    if (canDelete)
        m.deleteVertex(target);
}

void Widget::leftClickVertex(Vertex* v, const bool & state){
    //m.addEdge(v,state,ui->label);
    if (state){
        edgePoint.push_back(v);
        if (edgePoint.size()>=2){
            if (m.edgeExist(edgePoint.front(),edgePoint.back())){
                QMessageBox msg;
                msg.setText("Edge linked two selected vertex is already existed");
                msg.exec();
                edgePoint.back()->unSelect();
                edgePoint.pop_back();
                return;
            }
            bool ok=false;
            int distance=QInputDialog::getInt(this, "", "Plaese input the distance",0,0,INT_MAX,1,&ok);
            if (ok){

                Edge * e=new Edge(edgePoint.front(),edgePoint.back(), distance,ui->label);
                e->lower();
                connect(e,SIGNAL(deleteAction(Edge*,bool&)),this,SLOT(deleteEdgeAction(Edge*,bool&)));
                m.addEdge(e);
                //e->lower();
                m.connectVertex(edgePoint);
                edgePoint.back()->unSelect();
                edgePoint.front()->unSelect();
                edgePoint.clear();
            }else{
                edgePoint.back()->unSelect();
                edgePoint.pop_back();
            }
        }
    }else{
        edgePoint.remove(v);
    }
}

void Widget::deleteEdgeAction(Edge* target, bool & canDelete){
    qDebug()<<m.isLocked();
    canDelete=!m.isLocked();
    if (canDelete)
        m.deleteEdge(target);
}

void Widget::on_addEdgeBtn_toggled(bool checked)
{
    if (checked)
        ui->addVertexBtn->setChecked(!checked);
}

void Widget::on_startCalcalationBtn_toggled(bool checked)
{
    if (checked){
        ui->addVertexBtn->setChecked(!checked);
        ui->addEdgeBtn->setChecked(!checked);
        ui->addVertexBtn->setEnabled(false);
        ui->addEdgeBtn->setEnabled(false);
        ui->clearBtn->setEnabled(true);
        ui->showPathBtn->setEnabled(true);
    }else{
        ui->clearBtn->setEnabled(false);
        ui->showPathBtn->setEnabled(false);
    }
}

void Widget::startCalcalationAction(Vertex* target){
    //qDebug()<<"3";
    m.startDijkstra(target);
}

void Widget::showPathAction(Vertex* target){
    m.resetAllEdgeColor();
    m.showPath(target);
}

void Widget::on_clearBtn_clicked()
{   ui->clearBtn->setEnabled(false);
    ui->startCalcalationBtn->setChecked(false);
    ui->showPathBtn->setChecked(false);
    ui->showPathBtn->setEnabled(false);
    ui->addVertexBtn->setEnabled(true);
    ui->addEdgeBtn->setEnabled(true);
    m.clearResult();
}

void Widget::on_stepBtn_clicked()
{

}

void Widget::on_randGenBtn_clicked()
{
    bool vertexok=false;
    int numOfVertex=QInputDialog::getInt(this, "", "Plaese input the number of vertex:",1,1,INT_MAX,1,&vertexok);
    if (vertexok){
        bool edgeok=false;
        double denOfEdge=QInputDialog::getDouble(this,"","Please input the density of edges [0-1]:",0,0,1,2,&edgeok);
        if (edgeok){
                bool maxWeightok=false;
                int maxWeight=QInputDialog::getInt(this, "", "Plaese input the maximum edge weight",0,0,INT_MAX,1,&maxWeightok);
                if (maxWeightok){
                    srand (time(NULL));
                    for (int v=0;v<numOfVertex;++v){
                        int xpos=rand()%720+40;
                        int ypos=rand()%460+40;
                        addVertexAction(xpos,ypos);
                    }
                    //qDebug()<<"pass add vertex";
                    int numOfEdge=numOfVertex*(numOfVertex-1)/2*denOfEdge;
                    for (int e=0;e<numOfEdge;++e){
                        //qDebug()<<"before get";
                        Vertex* firstVertex=m.getVertex(rand()%numOfVertex);
                        Vertex* secondVertex=m.getVertex(rand()%numOfVertex);
                        //qDebug()<<"after get";
                        if (!m.edgeExist(firstVertex,secondVertex)){
                            Edge * e=new Edge(firstVertex,secondVertex, rand()%(maxWeight+1),ui->label);
                            e->lower();
                            connect(e,SIGNAL(deleteAction(Edge*,bool&)),this,SLOT(deleteEdgeAction(Edge*,bool&)));
                            m.addEdge(e);
                            std::list<Vertex*> edgeTwoPoint;
                            edgeTwoPoint.push_back(firstVertex);
                            edgeTwoPoint.push_back(secondVertex);
                            m.connectVertex(edgeTwoPoint);
                        }else{
                            --e;
                        }
                    }
                    //qDebug()<<"pass add edge";
                }
        }

    }
}

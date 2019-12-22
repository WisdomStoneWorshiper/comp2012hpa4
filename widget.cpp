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
    Vertex* v=new Vertex(event->x(), event->y(), ui->label);
    m.addVertex(v);
    //v->showTentativeDistance();
    connect(v,SIGNAL(deleteAction(Vertex*, bool &)), this, SLOT(rightClickVertex(Vertex*, bool &)));
    connect(ui->addEdgeBtn, SIGNAL(toggled(bool)),v, SLOT(catchEdgeBtnState(bool)));
    connect(v,SIGNAL(addEdgeAction(Vertex *, const bool &)),this,SLOT(leftClickVertex(Vertex *, const bool &)));
    connect(ui->startCalcalationBtn,SIGNAL(toggled(bool)),v,SLOT(catchStartBtnState(bool)));
    connect(v,SIGNAL(startCalAction(Vertex*)),this,SLOT(startCalcalationAction(Vertex*)));
    connect(v,SIGNAL(showP(Vertex*)),this,SLOT(showPathAction(Vertex*)));
    connect(ui->showPathBtn,SIGNAL(toggled(bool)),v,SLOT(catchShowPathBtnState(bool)));
    //connect(v,SIGNAL(moveEdgeAction(Vertex *)),this,SLOT(moveVertex(Vertex *)));
    }
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

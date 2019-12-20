#include "vertex.h"
#include <QDebug>
#include <QPainter>
#include <QBitmap>
#include <QFont>

Vertex::Vertex(int x, int y, QWidget * parent):QLabel(parent)
{
    id=nextID++;
    edgeBtnToggle=false;
    startBtnToggle=false;
    selected=false;
    visited=false;
    tentativeDistance=-1;
    setVisible(true);
    setGeometry(x-40,y-40,40,40);
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:black;");
    installEventFilter(this);
    //setText("y");
}

Vertex::~Vertex(){

}

int Vertex::getId() const{
    return id;
}

void Vertex::catchEdgeBtnState(bool state){
    edgeBtnToggle=state;
    qDebug()<<"yo";
}

void Vertex::catchStartBtnState(bool state){
    startBtnToggle=state;
}

bool Vertex::eventFilter(QObject *, QEvent *event) {
static QPoint lastPoint;
static bool isHover = false;
    if (event->type()==QEvent::MouseButtonPress){
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (rect().contains(e->pos()) &&(e->button()==Qt::RightButton)){
            setVisible(false);
            //update();
            deleteAction(this->id);
            this->deleteLater();

        }else if (e->button()==Qt::LeftButton){
            if (edgeBtnToggle==false && startBtnToggle==false){
            lastPoint = e->pos();
            isHover = true;
            qDebug()<<"t2";
            }else if (edgeBtnToggle && startBtnToggle==false){
                selected=!selected;
                addEdgeAction(this,selected);
                if (selected){
                    setStyleSheet("font-size : 25px;"
                                  "border: 3px solid ;"
                                  "border-radius : 20px;"
                                  "border-color:yellow;");
                }else{
                    setStyleSheet("font-size : 25px;"
                                  "border: 3px solid ;"
                                  "border-radius : 20px;"
                                  "border-color:black;");
                }
            }else if (startBtnToggle){
                startCalAction(this);
            }
        }
        //qDebug()<<"t5";
    }else if (event->type() == QEvent::MouseMove && isHover){
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y()+dy;

        move(new_x, new_y);
        //moveEdgeAction(this);
        //qDebug()<<"t3";
    }else if (event->type() == QEvent::MouseButtonRelease && isHover){

        isHover = !isHover;

    }else if (event->type()==QEvent::Paint){
        QLabel::paintEvent(static_cast<QPaintEvent*>(event));
        QFont font("Times",15);
        QPainter painter(this);
        QColor color = Qt::black;
        color.setAlpha(150);
        QPen pen(color);
        //pen.setWidth(10);
        painter.setPen(pen);
        painter.setFont(font);
        painter.drawText(QPoint(17,25),QString::number(tentativeDistance));
        //qDebug()<<tentativeDistance;
    }
}

void Vertex::showTentativeDistance(){
    qDebug()<<"j";
    setText(QString::number(id));
    repaint();
}

void Vertex::unSelect(){
    qDebug()<<"w4";
    selected=false;
    qDebug()<<"w5";
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:black;");
    qDebug()<<"w6";
}

void Vertex::setDistance(int d){
    tentativeDistance=d;
}

int Vertex::getDistance(){
    return tentativeDistance;
}

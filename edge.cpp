#include "edge.h"
#include <cmath>
//#include <QDebug>
#include <QBitmap>
#include <QPoint>
#include <QWidget>
#include <QLabel>

Edge::Edge(Vertex * firstPoint ,Vertex * secondPoint, int distance,QWidget* parent):QLabel(parent)
                                                                    , firstPoint(firstPoint)
                                                                    , secondPoint(secondPoint)
                                                                    , distance(distance)
{
    color = Qt::black;
    setVisible(true);
    update();
}

Edge::~Edge(){
    setVisible(false);
}

void Edge::paintEvent(QPaintEvent * e){
    //qDebug()<<"q3";
//    qDebug()<<firstPoint->x()<<secondPoint->x();
    drawAreaLefttop.setX(std::max(0, std::min(firstPoint->x(), secondPoint->x()) ));
    drawAreaLefttop.setY(std::max(0, std::min(firstPoint->y(), secondPoint->y()) ));

    int width = abs(firstPoint->x() - secondPoint->x()) +40;
    int height = abs(firstPoint->y() - secondPoint->y()) +40;
    //
    setGeometry(drawAreaLefttop.x(), drawAreaLefttop.y(), width, height);
    QLabel::paintEvent(e);
    QPixmap image(size());
    image.fill(Qt::transparent);
    QPainter painter(&image);
    color.setAlpha(150);
    QPen pen(color);
    QPoint lineLefttop;
    lineLefttop.setX(std::max(0, std::min(firstPoint->x(), secondPoint->x()) -20));
    lineLefttop.setY(std::max(0, std::min(firstPoint->y(), secondPoint->y()) -20));
    //qDebug()<<firstPoint<<secondPoint;

    QLineF line(firstPoint->pos()-lineLefttop,secondPoint->pos()-lineLefttop);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawLine(line);
    painter.drawText(QPoint(((firstPoint->pos()-lineLefttop)+(secondPoint->pos()-lineLefttop))/2) ,QString::number(distance));
    setPixmap(image);
    setMask(image.mask());
    //lower();
}

void Edge::mousePressEvent(QMouseEvent *ev){
    if (ev->button()==Qt::RightButton){
        setVisible(false);
        deleteAction(this);
        this->deleteLater();
    }
}

bool Edge::contains(Vertex *target){
    if (firstPoint==target || secondPoint==target){
        return true;
    }
    return false;
}

Vertex* Edge::getFirstPoint(){
    return firstPoint;
}

Vertex* Edge::getSecondPoint(){
    return secondPoint;
}

int Edge::getDistance(){
    return distance;
}

void Edge::turnBlue(){
    color=Qt::blue;
}

void Edge::resetColor(){
    color=Qt::black;
}

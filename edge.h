#ifndef EDGE_H
#define EDGE_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include "vertex.h"

using namespace std;
class Edge : public QLabel
{
    Q_OBJECT
public:
    Edge(Vertex *,Vertex *,int,QWidget*);
    ~Edge();
    Vertex * getFirstPoint();
    Vertex * getSecondPoint();
    bool contains(Vertex*);
    int getDistance();
signals:
    void deleteAction(Edge*);
public slots:
    //bool eventFilter(QObject *, QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *ev) override;

private:
    QPoint drawAreaLefttop;
    int distance;
    //QPainter * painter;
    Vertex * firstPoint;
    Vertex * secondPoint;
};

#endif // EDGE_H

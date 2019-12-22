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
    void turnBlue();
    void resetColor();
signals:
    void deleteAction(Edge*, bool &);
public slots:
    //bool eventFilter(QObject *, QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *ev) override;

private:
    QColor color;
    QPoint drawAreaLefttop;
    int distance;
    //QPainter * painter;
    Vertex * firstPoint;
    Vertex * secondPoint;
};

#endif // EDGE_H

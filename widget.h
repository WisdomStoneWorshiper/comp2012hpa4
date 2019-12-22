#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QInputDialog>
#include "manager.h"
#include "vertex.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void paintEvent(QPaintEvent *event) override;
    //bool event(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
public slots:
    void deleteEdgeAction(Edge*, bool &);
    void startCalcalationAction(Vertex*);
    void showPathAction(Vertex*);
private slots:
    void on_addVertexBtn_toggled(bool checked);
    void rightClickVertex(Vertex*, bool &);
    void leftClickVertex(Vertex*,const bool &);

    void on_addEdgeBtn_toggled(bool checked);
    void on_startCalcalationBtn_toggled(bool checked);

    void on_clearBtn_clicked();

private:
    Ui::Widget *ui;
    Manager m;
    std::list<Vertex *> edgePoint;
};
#endif // WIDGET_H

#ifndef VERTEX_H
#define VERTEX_H

#include <QLabel>
#include <QMouseEvent>

using namespace std;

class Vertex : public QLabel
{
    Q_OBJECT
public:
    Vertex(int, int, QWidget *);
    ~Vertex() override;
    static int nextID;
    int getId() const;
    void unSelect();
    void showTentativeDistance();
    void setDistance(int);
    int getDistance();
    void turnBlue();
    void turnGreen();
    void turnRed();
    void turnGrey();
    void turnCyan();
signals:
    void deleteAction(Vertex*, bool &);
    void addEdgeAction(Vertex*,const bool &);
    void startCalAction(Vertex*);
    void showP(Vertex*);
    //void moveEdgeAction(Vertex*);
public slots:
    bool eventFilter(QObject *, QEvent *event) override;
    void catchEdgeBtnState(bool);
    void catchStartBtnState(bool);
    void catchShowPathBtnState(bool);
private:
    int id, tentativeDistance;
    bool edgeBtnToggle, selected, visited, startBtnToggle, showPathToggle;
};

#endif // VERTEX_H

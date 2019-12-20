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
signals:
    void deleteAction(const int &);
    void addEdgeAction(Vertex*,const bool &);
    void startCalAction(Vertex*);
    //void moveEdgeAction(Vertex*);
public slots:
    bool eventFilter(QObject *, QEvent *event) override;
    void catchEdgeBtnState(bool);
    void catchStartBtnState(bool);
private:
    int id, tentativeDistance;
    bool edgeBtnToggle, selected, visited, startBtnToggle;
};

#endif // VERTEX_H

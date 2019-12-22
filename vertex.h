#ifndef VERTEX_H
#define VERTEX_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QBitmap>
#include <QFont>

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
    void setDistance(const int &);
    int getDistance();
    void turnBlue();
    void turnGreen();
    void turnRed();
    void turnGrey();
    void turnCyan();
    void turnBlack();
signals:
    void deleteAction(Vertex *, bool &);
    void addEdgeAction(Vertex *, const bool &);
    void startCalAction(Vertex *);
    void showP(Vertex *);
public slots:
    bool eventFilter(QObject *, QEvent *event) override;
    void catchEdgeBtnState(const bool &);
    void catchStartBtnState(const bool &);
    void catchShowPathBtnState(const bool &);

private:
    int id, tentativeDistance;
    bool edgeBtnToggle, selected, visited, startBtnToggle, showPathToggle;
};

#endif // VERTEX_H

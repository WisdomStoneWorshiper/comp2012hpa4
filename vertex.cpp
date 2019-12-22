#include "vertex.h"

Vertex::Vertex(int x, int y, QWidget *parent) : QLabel(parent)
{
    id = nextID++;
    edgeBtnToggle = false;
    startBtnToggle = false;
    showPathToggle = false;
    selected = false;
    visited = false;
    tentativeDistance = -1;
    setVisible(true);
    setGeometry(x - 40, y - 40, 40, 40);
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:black;"
                  "background-color:white;");
    installEventFilter(this);
}

Vertex::~Vertex()
{
}

int Vertex::getId() const
{
    return id;
}

void Vertex::catchEdgeBtnState(const bool &state)
{
    edgeBtnToggle = state;
}

void Vertex::catchStartBtnState(const bool &state)
{
    startBtnToggle = state;
}

void Vertex::catchShowPathBtnState(const bool &state)
{
    showPathToggle = state;
}

bool Vertex::eventFilter(QObject *, QEvent *event)
{
    static QPoint lastPoint;
    static bool isHover = false;
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if (rect().contains(e->pos()) && (e->button() == Qt::RightButton))
        {
            bool canDelete;
            deleteAction(this, canDelete);
            if (canDelete)
            {
                setVisible(false);
                this->deleteLater();
            }
        }
        else if (e->button() == Qt::LeftButton)
        {

            if (startBtnToggle)
                startCalAction(this);

            if (showPathToggle)
            {

                showP(this);
            }

            if (edgeBtnToggle == false)
            {
                lastPoint = e->pos();
                isHover = true;
            }
            else if (edgeBtnToggle && startBtnToggle == false)
            {
                selected = !selected;
                addEdgeAction(this, selected);
                if (selected)
                {
                    setStyleSheet("font-size : 25px;"
                                  "border: 3px solid ;"
                                  "border-radius : 20px;"
                                  "border-color:yellow;"
                                  "background-color:white;");
                }
                else
                {
                    setStyleSheet("font-size : 25px;"
                                  "border: 3px solid ;"
                                  "border-radius : 20px;"
                                  "border-color:black;"
                                  "background-color:white;");
                }
            }
        }
    }
    else if (event->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();
        int new_x = x() + dx;
        int new_y = y() + dy;

        move(new_x, new_y);
    }
    else if (event->type() == QEvent::MouseButtonRelease && isHover)
    {

        isHover = !isHover;
    }
    else if (event->type() == QEvent::Paint)
    {

        if (tentativeDistance > -1)
        {
            QLabel::paintEvent(static_cast<QPaintEvent *>(event));
            QFont font("Times", 15);
            QPainter painter(this);
            QColor color = Qt::black;
            QPen pen(color);
            painter.setPen(pen);
            painter.setFont(font);
            painter.drawText(QPoint(17, 25), QString::number(tentativeDistance));
        }
    }
}

void Vertex::showTentativeDistance()
{
    //qDebug()<<"j";
    setText(QString::number(id));
    repaint();
}

void Vertex::unSelect()
{
    selected = false;
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:black;"
                  "background-color:white;");
}

void Vertex::setDistance(const int &d)
{
    tentativeDistance = d;
}

int Vertex::getDistance()
{
    return tentativeDistance;
}

void Vertex::turnBlue()
{
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:blue;"
                  "background-color:white;");
}

void Vertex::turnGreen()
{
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:green;"
                  "background-color:white;");
}

void Vertex::turnRed()
{
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:red;"
                  "background-color:white;");
}

void Vertex::turnGrey()
{
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:grey;"
                  "background-color:white;");
}

void Vertex::turnCyan()
{
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:cyan;"
                  "background-color:white;");
}

void Vertex::turnBlack()
{
    setStyleSheet("font-size : 25px;"
                  "border: 3px solid ;"
                  "border-radius : 20px;"
                  "border-color:black;"
                  "background-color:white;");
}

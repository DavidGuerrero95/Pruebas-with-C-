#include "qvista.h"

QVista::QVista(QWidget *parent)
    :QGraphicsView(parent)
{

}

QVista::QVista(QGraphicsScene *scene, QWidget *parent)
    :QGraphicsView(scene, parent)
{

}

QVista::~QVista()
{
    this->close();
}

void QVista::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numPixels.isNull())
    {
        if(numPixels.manhattanLength()<0)
            emit Zoomout();
        else
            emit Zoomin();
    }
    else if (!numDegrees.isNull())
    {
        QPoint numSteps = numDegrees / 15;
        if(numSteps.y()<0)
            emit Zoomout();
        else
            emit Zoomin();
    }

    event->accept();
}

void QVista::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        PM.setX(PO.x()-(event->pos()).x());
        PM.setY(PO.y()-(event->pos()).y());
        qDebug()<<PM;
        emit draggmouse();
    }
    PO=event->pos();
}

int QVista::get_movedx()
{
    return PM.x();
}

int QVista::get_movedy()
{
    return PM.y();
}



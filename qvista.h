#ifndef QVISTA_H
#define QVISTA_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>

class QVista : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QVista(QWidget *parent = Q_NULLPTR);
    explicit QVista(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);
    ~QVista();
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int get_movedx();
    int get_movedy();

signals:
    void Zoomin();
    void Zoomout();
    void draggmouse();

private:
    QPoint PO,PM;
};

#endif // QVISTA_H

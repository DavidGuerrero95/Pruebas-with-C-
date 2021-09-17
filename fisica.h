#ifndef FISICA_H
#define FISICA_H
#include <math.h>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <list>


class fisica: public QGraphicsItem
{
private:
    double g=0;
    double delta=0;
    double x2=0;
    double x=0;
    double y2=0;
    double y=0;
    double vx=0;
    double vy=0;
    double V=0;
    double alfa=0;
    double ax=0;
    double ay=0;
    double m=1;
    double r=0;  //Radio de la esfera

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    fisica();
    fisica(double xx, double yy, double masa,double rad, double vvx, double vvy, double xx2, double yy2);
    double getx();
    double gety();
    double getm();
    void calc_a(std::list <fisica*> *arr);
    void actualizar();
    ~fisica();
};

#endif // FISICA_H

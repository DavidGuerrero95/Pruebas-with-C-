#include "mainw.h"
#include "ui_mainw.h"

MainW::MainW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainW)
{
    ui->setupUi(this);
    dato=new Intro(this);
    dato->hide();
    connect(dato,SIGNAL(ingresa()),this,SLOT(Crear()));
    connect(dato,SIGNAL(cancela()),this,SLOT(Cerrar()));
    connect(ui->grafica,SIGNAL(Zoomin()),this,SLOT(Zoom_in()));
    connect(ui->grafica,SIGNAL(Zoomout()),this,SLOT(Zoom_out()));
    connect(ui->grafica,SIGNAL(draggmouse()),this,SLOT(Moved()));
    scene=new QGraphicsScene;
    scene2=new QGraphicsScene;
    timer=new QTimer;
    ui->grafica->setScene(scene);
    ui->grafica_2->setScene(scene2);
    scene->setSceneRect(-500,-250,1002,502);
    scene2->setSceneRect(0,0,1002,502);
    connect(timer,SIGNAL(timeout()),this,SLOT(Actualizar()));
    timer->setSingleShot(false);
    timer->start(1);
}

void MainW::keyReleaseEvent(QKeyEvent *event)//Para tab lab 4
{
    if(ui->tabWidget->currentIndex()==0)
    {
        if(event->key()==Qt::Key_Space)
            scene->setSceneRect(-500,-250,1002,502);
    }
}

MainW::~MainW()
{
    delete ui;
}


void MainW::Actualizar()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        for(std::list<fisica*>::iterator it=sistema.begin(); it!=sistema.end();++it)
            (*it)->calc_a(&sistema);
        for(std::list<fisica*>::iterator it=sistema.begin(); it!=sistema.end();++it)
            (*it)->actualizar();
    }
    else if(ui->tabWidget->currentIndex()==1)
    {
        //kk;
    }
}

void MainW::Crear()
{
    dato->hide();
    QString name=QFileDialog::getOpenFileName(this,tr("Archivo de Cuerpos"), ".//cuerpos","Text File (*.txt)");
    QStringList lista;
    QFile file(name);
    int n=dato->getvalor(); bool all=false;
    if(n==0)
        all=true;
    if(file.open(QIODevice::ReadOnly))
    {
        while(all || n>0)
        {
            if(!all)
                n--;
            name=file.readLine(1000);
            lista=name.split(",");
            qDebug()<<lista;
            if(lista.size()==6)
            {
                sistema.push_back(new fisica((lista.at(0)).toDouble(),(lista.at(1)).toDouble(),(lista.at(2)).toDouble(),(lista.at(3)).toDouble(),(lista.at(4)).toDouble(),(lista.at(5)).toDouble(),0,0));
                scene->addItem(sistema.back());
            }
            else
            {
                break;
            }
        }
    }
    connect(timer,SIGNAL(timeout()),this,SLOT(Actualizar()));
}

void MainW::Cerrar()
{
    dato->hide();
    connect(timer,SIGNAL(timeout()),this,SLOT(Actualizar()));
}

void MainW::on_actionSalir_triggered()
{
    this->close();
}

void MainW::on_actionReiniciar_triggered()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        cuerpos=0;
        sistema.clear();
        scene=new QGraphicsScene;
        ui->grafica->setScene(scene);
        ui->grafica->scale(pow(scale,zoom),pow(scale,zoom));
        zoom=0;
        scene->setSceneRect(-500,-250,1002,502);
        scene->addRect(-250,-250,502,502);
    }
    else if(ui->tabWidget->currentIndex()==1)
    {
        cuerpos2=0;
        sistema2.clear();
        scene2=new QGraphicsScene;
        ui->grafica_2->setScene(scene2);
        scene2->setSceneRect(0,0,1002,502);
    }
}

void MainW::on_actionCrear_triggered()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(Actualizar()));
        dato->show();
    }
}

void MainW::Zoom_in()//Para tab lab 4
{
    ui->grafica->scale(scale,scale);
    zoom--;
}


void MainW::Zoom_out()//Para tab lab 4
{
    ui->grafica->scale(1/scale,1/scale);
    zoom++;
}

void MainW::Moved()//Para tab lab 4
{
    QRectF *rec= new QRectF(scene->sceneRect());
    qDebug()<<*rec;
    rec->translate(ui->grafica->get_movedx()*pow(scale,zoom),ui->grafica->get_movedy()*pow(scale,zoom));
    qDebug()<<*rec;
    qDebug()<<zoom;
    scene->setSceneRect(*rec);
}

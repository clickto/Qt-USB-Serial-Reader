#include "SerialGraph.h"

SerialGraph::SerialGraph(QWidget *parent) : QWidget(parent)
{
  serial_port = new QSerialPort(this);

  graphics_scene = new QGraphicsScene(this);
  graphics_view = new QGraphicsView(graphics_scene, this);
  graphics_scene->setSceneRect(0,0,1000,1000);

  graphics_scene->addLine(20,30,700,900,QPen(QBrush(Qt::SolidPattern),3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));


  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->addWidget(graphics_view);



}


#ifndef SERIALGRAPH_H
#define SERIALGRAPH_H

#include <QWidget>
#include <QThread>
#include <QSerialPort>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QVBoxLayout>

class SerialGraph : public QWidget
{
  Q_OBJECT
public:
  explicit SerialGraph(QWidget *parent = 0);


private:
  QSerialPort *serial_port;
  QGraphicsScene *graphics_scene;
  QGraphicsView *graphics_view;
};

#endif // SERIALGRAPH_H

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

  console = new Console(this);
  device_viewer = new DeviceViewer(console, this);

  QHBoxLayout *main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->addWidget(device_viewer);
  main_layout->addWidget(console);

//  QPalette palette;
//  palette.setColor(QPalette::Base, QColor(33,152,157,200));

//  this->setPalette(palette);
  this->setAttribute(Qt::WA_TranslucentBackground, true);
  this->setMinimumWidth(400);
  this->setFixedHeight(500);
  this->setParent(parent);
}

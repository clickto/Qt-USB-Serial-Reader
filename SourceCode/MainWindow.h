#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGroupBox>
#include <QSplitter>

#include "DeviceViewer.h"
#include "SerialGraph.h"
#include "Console.h"

class MainWindow : public QWidget
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = 0);

private:
  DeviceViewer *device_viewer;
  Console *console;

};

#endif // MAINWINDOW_H

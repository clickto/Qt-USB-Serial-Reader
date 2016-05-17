#ifndef WIDGET_H
#define WIDGET_H

#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMap>

#include "SerialThread.h"
#include "GlobalData.h"
#include "Console.h"

//class SerialThread;

class DeviceViewer : public QWidget
{
  Q_OBJECT

public:
  DeviceViewer(Console *console, QWidget *parent = 0);
  ~DeviceViewer();

  Serial *my_serial;

private:
//  QGroupBox *group_box;
  QLabel *port_label;
  QComboBox *port_combo;
  QLabel *baud_rate_label;
  QComboBox *baud_rate_combo;
  QLabel *location_label;
  QLabel *description_label;
  QLabel *manufacturer_label;
  QLabel *seria_number_label;
  QLabel *vendor_identifier_label;
  QLabel *product_identifier_label;
  QLabel *busy_label;
  QPushButton *refresh_btn;
  QPushButton *advanced_btn;
  QPushButton *start_btn;
  QPushButton *stop_btn;

  QMap<QString, SerialDevice> device_map;

  SerialSettings serial_settings;

  Console *my_console;

private slots:
  void onPortComboChanged(QString current_device);
  void onBaudRateChanged(QString baudRate);
  void onPortInfoRefreshed();
  void onStarted();
  void onStopped();
};

#endif // WIDGET_H

#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include <QMessageBox>
#include <QSerialPort>
#include <QDebug>
#include <QMap>

#include "GlobalData.h"





class Serial : public QObject
{
  Q_OBJECT
public:
  explicit Serial(QObject *parent = 0);

  void setSettings(struct SerialSettings *serialSettings);
  void startSerial();
  void closeSerial();

private:
  QSerialPort *serial_port;
  QByteArray data_array;

private slots:
  void readData();
  void handleError(QSerialPort::SerialPortError error);

signals:
  void messageRead(QByteArray);
};

#endif // SERIALTHREAD_H

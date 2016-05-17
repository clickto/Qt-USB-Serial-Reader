#include "SerialThread.h"

Serial::Serial(QObject *parent) : QObject(parent)
{
  serial_port = new QSerialPort(this);

  connect(serial_port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
  connect(serial_port, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Serial::setSettings(SerialSettings *serialSettings)
{
  serial_port->setPortName(serialSettings->port_name);
  serial_port->setBaudRate(serialSettings->baud_rate);
  serial_port->setDataBits(serialSettings->data_bits);
  serial_port->setParity(serialSettings->parity);
  serial_port->setStopBits(serialSettings->stop_bits);
  serial_port->setFlowControl(serialSettings->flow_control);
}

void Serial::startSerial()
{

  if (serial_port->open(QIODevice::ReadOnly))
    {
      qDebug()<<"connection established";

    }
  else
    {
      qDebug()<<serial_port->errorString();
//      QMessageBox::critical(this, tr("Error"), serial_port->errorString());
    }

}

void Serial::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
      {
        QMessageBox::critical(0, "Critical Error", serial_port->errorString());
        closeSerial();
      }
}

void Serial::closeSerial()
{
    if (serial_port->isOpen())
      {
        serial_port->close();
      }
}

void Serial::readData()
{
  QByteArray data = serial_port->readAll();
  data_array.append(data);
  emit messageRead(data);

}

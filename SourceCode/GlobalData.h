#ifndef GLOBALDATA_H
#define GLOBALDATA_H


struct SerialDevice{
  QString port_name;
  QString location;
  QString path;
  QString description;
  QString manufacturer;
  QString seria_number;
  QString vendor_identifier;
  QString product_identifier;
  bool busy;
};

struct SerialSettings {
    QString port_name;
    qint32 baud_rate = static_cast<QSerialPort::BaudRate>(9600);
    QSerialPort::DataBits data_bits = static_cast<QSerialPort::DataBits>(8);
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stop_bits = static_cast<QSerialPort::StopBits>(1);
    QSerialPort::FlowControl flow_control = QSerialPort::NoFlowControl;
};


#endif // GLOBALDATA_H

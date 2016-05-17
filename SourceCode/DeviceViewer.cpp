#include "DeviceViewer.h"

DeviceViewer::DeviceViewer(Console *console, QWidget *parent)
  : QWidget(parent)
{
  my_console = console;

  this->setAutoFillBackground(true);
  this->setMinimumWidth(400);
  this->setParent(parent);

//  group_box = new QGroupBox("Device Viewer", this);
  port_label = new QLabel("Port:", this);
  port_combo = new QComboBox(this);
  baud_rate_label = new QLabel("Baud Rate:", this);
  baud_rate_combo = new QComboBox(this);
  location_label = new QLabel("Location Label:", this);
  description_label = new QLabel("Description:", this);
  manufacturer_label = new QLabel("Manufacturer:", this);
  seria_number_label = new QLabel("Seria Number:", this);
  vendor_identifier_label = new QLabel("Vendor Identifier:", this);
  product_identifier_label = new QLabel("Product Identifier:", this);
  busy_label = new QLabel("Busy:", this);
  refresh_btn = new QPushButton("Refresh");
  advanced_btn = new QPushButton("Advanced Settings");
  start_btn = new QPushButton("Start!");
  stop_btn = new QPushButton("Stop!");

  port_combo->setFixedWidth(300);

  baud_rate_combo->addItem("1200", QSerialPort::Baud1200);
  baud_rate_combo->addItem("2400", QSerialPort::Baud2400);
  baud_rate_combo->addItem("4800", QSerialPort::Baud4800);
  baud_rate_combo->addItem("9600", QSerialPort::Baud9600);
  baud_rate_combo->addItem("19200", QSerialPort::Baud19200);
  baud_rate_combo->addItem("38400", QSerialPort::Baud38400);
  baud_rate_combo->addItem("57600", QSerialPort::Baud57600);
  baud_rate_combo->addItem("115200", QSerialPort::Baud115200);
  baud_rate_combo->setCurrentIndex(3);
  baud_rate_combo->setFixedWidth(300);

  refresh_btn->setFixedWidth(80);
  advanced_btn->setFixedWidth(215);
  start_btn->setFixedWidth(300);
  stop_btn->setFixedWidth(300);
  stop_btn->setDisabled(true);

  QHBoxLayout *button_layout = new QHBoxLayout();
  button_layout->setAlignment(Qt::AlignLeft);
  button_layout->setContentsMargins(0,0,0,0);
  button_layout->setSpacing(10);
  button_layout->addWidget(refresh_btn);
  button_layout->addWidget(advanced_btn);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(port_label);
  main_layout->addWidget(port_combo);
  main_layout->addWidget(baud_rate_label);
  main_layout->addWidget(baud_rate_combo);
  main_layout->addWidget(location_label);
  main_layout->addWidget(description_label);
  main_layout->addWidget(manufacturer_label);
  main_layout->addWidget(seria_number_label);
  main_layout->addWidget(vendor_identifier_label);
  main_layout->addWidget(product_identifier_label);
  main_layout->addWidget(busy_label);
  main_layout->addLayout(button_layout);
  main_layout->addWidget(start_btn);
  main_layout->addWidget(stop_btn);

//  group_box->setLayout(main_layout);
//  group_box->setAutoFillBackground(true);
//  group_box->setPalette(p);

//  QVBoxLayout *main_layout = new QVBoxLayout(this);
//  main_layout->setContentsMargins(0,0,0,0);
//  main_layout->addWidget(group_box);



  connect(baud_rate_combo, SIGNAL(currentTextChanged(QString)), this, SLOT(onBaudRateChanged(QString)));
  onBaudRateChanged(baud_rate_combo->currentText());

  connect(port_combo, SIGNAL(currentTextChanged(QString)), this, SLOT(onPortComboChanged(QString)));
  onPortComboChanged(port_combo->currentText());

  connect(refresh_btn, SIGNAL(clicked(bool)), this, SLOT(onPortInfoRefreshed()));
  onPortInfoRefreshed();

  connect(start_btn, SIGNAL(clicked(bool)), this, SLOT(onStarted()));
  connect(stop_btn, SIGNAL(clicked(bool)), this, SLOT(onStopped()));
}

DeviceViewer::~DeviceViewer()
{
//  serial_thread->quit();
}

void DeviceViewer::onPortComboChanged(QString current_device)
{
  SerialDevice serial_device = device_map.value(current_device);
  location_label->setText(QString("Location Label:\t" + serial_device.location));
  description_label->setText(QString("Description:\t" + serial_device.description));
  manufacturer_label->setText(QString("Manufacturer:\t" + serial_device.manufacturer));
  seria_number_label->setText(QString("Seria Number:\t" + serial_device.seria_number));
  vendor_identifier_label->setText(QString("Vendor Identifier:\t" + serial_device.vendor_identifier));
  product_identifier_label->setText(QString("Product Identifier:\t" + serial_device.product_identifier));
  busy_label->setText(QString("Busy:\t\t" + QString(serial_device.busy ? "Yes" : "No")));

  serial_settings.port_name = current_device;


}

void DeviceViewer::onBaudRateChanged(QString baudRate)
{
  serial_settings.baud_rate = static_cast<QSerialPort::BaudRate>(baud_rate_combo->currentData().toInt());
  qDebug()<<"current baud rate:"<<QString::number(serial_settings.baud_rate);
}

void DeviceViewer::onPortInfoRefreshed()
{
  device_map.clear();
  port_combo->clear();

  foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
      SerialDevice serial_device;
      serial_device.port_name = info.portName();
      serial_device.location = info.systemLocation();
      serial_device.description = info.description();
      serial_device.manufacturer = info.manufacturer();
      serial_device.seria_number = info.serialNumber();
      serial_device.vendor_identifier = (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString());
      serial_device.product_identifier = (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());
      serial_device.busy = info.isBusy();

      if(device_map.keys().contains(serial_device.port_name))
        {
          device_map.remove(serial_device.port_name);
          device_map.insert(serial_device.port_name, serial_device);
        }
      else
        {
          port_combo->addItem(serial_device.port_name);
          device_map.insert(serial_device.port_name, serial_device);
        }
    }

  onPortComboChanged(port_combo->currentText());
}

void DeviceViewer::onStarted()
{ 
  port_combo->setDisabled(true);
  baud_rate_combo->setDisabled(true);
  refresh_btn->setDisabled(true);
  advanced_btn->setDisabled(true);
  start_btn->setDisabled(true);
  stop_btn->setDisabled(false);
  my_console->setDisabled(true);
  my_console->clear();

  my_serial = new Serial(this);
  my_serial->setSettings(&serial_settings);
  my_serial->startSerial();

  connect(my_serial, SIGNAL(messageRead(QByteArray)), my_console, SLOT(putData(QByteArray)));

  qDebug()<<serial_settings.baud_rate;
  qDebug()<<serial_settings.data_bits;
  qDebug()<<serial_settings.flow_control;
  qDebug()<<serial_settings.parity;
  qDebug()<<serial_settings.port_name;
  qDebug()<<serial_settings.stop_bits;

}

void DeviceViewer::onStopped()
{
  port_combo->setDisabled(false);
  baud_rate_combo->setDisabled(false);
  refresh_btn->setDisabled(false);
  advanced_btn->setDisabled(false);
  start_btn->setDisabled(false);
  stop_btn->setDisabled(true);
  my_console->setDisabled(false);


  my_serial->closeSerial();
  my_serial->deleteLater();
}

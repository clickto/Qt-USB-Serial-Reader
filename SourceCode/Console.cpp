#include "Console.h"

Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
{
    document()->setMaximumBlockCount(100);
    QPalette p;
    p.setColor(QPalette::Base, QColor(50,50,50,150));
    p.setColor(QPalette::Text, Qt::green);
    this->setMinimumWidth(400);
    this->setPalette(p);
    this->setParent(parent);
}

void Console::putData(const QByteArray &data)
{
    insertPlainText(QString(data));

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}


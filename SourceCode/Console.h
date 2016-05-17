#ifndef CONSOLE_H
#define CONSOLE_H

#include <QtCore/QDebug>

#include <QScrollBar>
#include <QPlainTextEdit>

class Console : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit Console(QWidget *parent = 0);

public slots:
    void putData(const QByteArray &data);
};


#endif // CONSOLE_H

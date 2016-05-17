#ifndef THREADDATA_H
#define THREADDATA_H

#include <QThread>

class ThreadData : public QThread
{
public:
  explicit ThreadData(QObject *parent = 0);
  ~ThreadData();

protected:
  void run();

private:
  bool quit;

};

#endif // THREADDATA_H

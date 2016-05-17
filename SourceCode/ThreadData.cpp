#include "ThreadData.h"

ThreadData::ThreadData(QObject *parent) : QThread(parent)
{

}

ThreadData::~ThreadData()
{

}

void ThreadData::run()
{
  while(!quit)
    {

    }
}

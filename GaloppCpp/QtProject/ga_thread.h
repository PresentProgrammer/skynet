#ifndef GA_THREAD_H
#define GA_THREAD_H

#include <QObject>

class GA_Thread : public QThread
{
public:
  GA_Thread();
  ~GA_Thread();
};

#endif // GA_THREAD_H

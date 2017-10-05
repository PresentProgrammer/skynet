#ifndef GATHREAD_H
#define GATHREAD_H

#include <QtCore>
#include <QProgressBar>
#include <string>

class GeneticAlgorithm;

class GAThread : public QThread
{
  Q_OBJECT
private:
  GeneticAlgorithm * GA_ptr;
  std::string fileName;
  QProgressBar * progressBar;

public:
  GAThread(QObject * parent = 0);
  ~GAThread();

  void setAttributes(GeneticAlgorithm * ga_ptr, std::string file_name,
              QProgressBar * progress_bar);
  void run();
};

#endif // GATHREAD_H

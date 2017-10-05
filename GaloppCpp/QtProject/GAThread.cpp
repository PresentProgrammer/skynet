#include "GAThread.h"
#include "GeneticAlgorithm.h"
#include <QtCore>
#include <QMessageBox>
#include <string>
#include <iostream>

GAThread::GAThread(QObject * parent) : QThread(parent)
{

}

GAThread::~GAThread()
{

}

void GAThread::setAttributes(GeneticAlgorithm * ga_ptr, string file_name,
            QProgressBar * progress_bar)
{
  GA_ptr = ga_ptr;
  fileName = file_name;
  progressBar = progress_bar;
}

void GAThread::run()
{

}


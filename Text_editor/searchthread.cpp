#include "searchthread.h"

#include <QDirIterator>

SearchThread::SearchThread(QStringList fileNames, QString path, QDir currentDir) : fileNames(fileNames), path(path), currentDir(currentDir)
{}

void SearchThread::run()
{
    QDirIterator it(path, fileNames, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    path = it.next();
    emit result(path);
}

#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H

#include <QDir>
#include <QObject>
#include <QThread>

class SearchThread : public QThread
{
    Q_OBJECT
public:
    SearchThread(QStringList fileNames, QString path, QDir currentDir);
    void run() override;

signals:
    void result(QString);

private:
    QStringList fileNames;
    QString path;
    QDir currentDir;
};

#endif // SEARCHTHREAD_H

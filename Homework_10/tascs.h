#ifndef TASCS_H
#define TASCS_H

#include <QApplication>
#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileDialog>

class Tascs : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QString tascs WRITE AddTasc);
public:
    explicit Tascs(QObject *parent = nullptr);
    virtual ~Tascs();
    Q_INVOKABLE void addTasc(QString);
    Q_INVOKABLE int getTascsCount();
    Q_INVOKABLE void save_as();
    void save();
    Q_INVOKABLE void open();

private:
    QWidget *widget;
    QString tascs;
    QFile file;
    QString lastUsedFile;
    int numberOfTascs;
};

#endif // TASCS_H

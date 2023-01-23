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
    void save_as();
    void open();

private:
    QWidget *widget;
    QString tascs;
    QFile file;
};

#endif // TASCS_H

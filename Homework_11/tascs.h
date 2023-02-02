#ifndef TASCS_H
#define TASCS_H

#include <QApplication>
#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include "tablesqlview.h"

class Tascs : public QObject
{
    Q_OBJECT

public:
    explicit Tascs(QObject *parent = nullptr);
    virtual ~Tascs();
    Q_INVOKABLE void addTasc(QString, QString, QString);
    Q_INVOKABLE int getTascsCount();
    Q_INVOKABLE void viewTascs();

private:
    QWidget *widget;
    QString tascs;
    QFile file;
    QString lastUsedFile;
    int numberOfTascs;
    TableSQLView tsv;
};

#endif // TASCS_H

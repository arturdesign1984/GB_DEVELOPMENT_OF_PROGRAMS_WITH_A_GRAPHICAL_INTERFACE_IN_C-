#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "blockscheme.h"
#include "firstscene.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FirstScene *scence;

protected:

private slots:

};
#endif // MAINWINDOW_H

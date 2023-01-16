#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    scence = new FirstScene(this);
    setScene(scence);

    connect(static_cast<BlockScheme*>(sender()), SIGNAL(reDraw()), this, SLOT(reDraw()));
}

MainWindow::~MainWindow()
{
    delete scence;
}

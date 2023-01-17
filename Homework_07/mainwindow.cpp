#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QGraphicsView(parent)
{
    scence = new FirstScene(this);
    setScene(scence);
}

MainWindow::~MainWindow()
{
    delete scence;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.y() > 0)
    {
        this->scale(1.1, 1.1);
    }
    else
    {
        this->scale(0.9, 0.9);
    }
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Plus)
    {
        this->scale(1.1, 1.1);
    }
    else if (event->key() == Qt::Key_Minus)
    {
        this->scale(0.9, 0.9);
    }
    event->accept();
}

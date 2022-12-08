#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Calculate_clicked()
{
    int a = ui->lineEdit_a->text().toInt();
    int b = ui->lineEdit_b->text().toInt();
    int c = ui->lineEdit_c->text().toInt();

    int d = qPow(b, 2) - 4*a*c;

    if(d < 0 || (a == 0 && b == 0 && c == 0) || (b == 0 && a != 0 && ((-c / a) < 0)))
    {
        ui->textEdit_result->setText("Нет корней");
    }
    else if (d == 0)
    {
        ui->textEdit_result->setText("x = " + QString::number(-b / (2 * a)));
    }
    else if (a == 0)
    {
        ui->textEdit_result->setText("x = " + QString::number(-c / b));
    }
    else if (b == 0 && c == 0)
    {
        ui->textEdit_result->setText("x = 0");
    }
    else if (b == 0 && (-c / a > 0))
    {
        ui->textEdit_result->setText("x1 = " +
                                     QString::number(qSqrt(-c / a)) +
                                     ", x2 = " +
                                     QString::number(-qSqrt(-c / a))
                                     );
    }
    else if (c == 0)
    {
        ui->textEdit_result->setText("x1 = 0, x2 = " +
                                     QString::number(-b / a)
                                     );
    }
    else
    {
        ui->textEdit_result->setText("x1 = " +
                                     QString::number((-b - qSqrt(d)) / (2 * a)) +
                                     ", x2 = " +
                                     QString::number((-b + qSqrt(d)) / (2 * a))
                                     );
    }
}


void MainWindow::on_pushButtonAngle_clicked()
{
    int a = ui->lineEdit_side_a->text().toInt();
    int b = ui->lineEdit_side_b->text().toInt();
    double angle = 0;

    if(ui->radioButton->isChecked())
    {
        angle = qDegreesToRadians(ui->lineEdit_angle->text().toDouble());
    }
    else
    {
        angle = ui->lineEdit_angle->text().toDouble();
    }
    double res = qSqrt(qPow(a, 2) + qPow(b, 2) - (2 * a * b * qCos(angle)));
    ui->lineEditResultAngle->setText(QString::number(res));
}




void MainWindow::on_pushButtonAdd_clicked()
{
    QString text = ui->plainTextEditLeft->toPlainText();
    ui->plainTextEditRight->appendPlainText(text);
}



void MainWindow::on_pushButtonReplaseText_clicked()
{
    QString text = ui->plainTextEditLeft->toPlainText();
    ui->plainTextEditRight->setPlainText(text);
}


void MainWindow::on_pushButtonAddHTML_clicked()
{
    ui->plainTextEditLeft->appendHtml("<font color='red'>Hello</font>");
}


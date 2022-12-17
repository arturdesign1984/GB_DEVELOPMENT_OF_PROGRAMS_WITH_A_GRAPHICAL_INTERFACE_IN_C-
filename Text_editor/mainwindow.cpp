#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

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


void MainWindow::on_info_clicked()
{
    file.setFileName(":/src/info.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(file.readAll());
        file.close();
    } else
    {
        qDebug() << "Файл info.txt отсутствует.\n";
    }
}


void MainWindow::on_save_as_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QString::fromUtf8("Сохранить файл"),
                                                    QDir::currentPath(),
                                                    "Text (*.txt);;All files (*.*)");

    file.setFileName(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QString text = ui->textEdit->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba, ba.length());
        file.close();
    } else
    {
        qDebug() << "Ошибка при сохранении.\n";
    }
}


void MainWindow::on_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Открыть файл"),
                                                    QDir::currentPath(),
                                                    "Text (*.txt);;All files (*.*)");

    file.setFileName(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(file.readAll());
        file.close();
    } else
    {
        qDebug() << "Не удалось открыть файл " << fileName << ".\n";
    }
}


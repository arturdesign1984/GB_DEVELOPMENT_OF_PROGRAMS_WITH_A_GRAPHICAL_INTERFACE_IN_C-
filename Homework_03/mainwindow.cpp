#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    fileData = "";
    filePath = QFileDialog::getOpenFileName(this,
                                                        QString::fromUtf8("Открыть файл"),
                                                        QDir::currentPath(),// - директория программы; ( QDir::homePath() ), - директория пользователя;
                                                        "HTML (*.html);;All files (*.*)");


    int index = filePath.lastIndexOf('/') + 1;
    if (index  != -1)
    {
        fileName = filePath.mid(index);
    }
    ui->label->setText(fileName);
    file.setFileName(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        fileData = file.readAll();
        file.close();
    } else
    {
        qDebug() << "Не удалось открыть файл " << fileName << ".\n";
        ui->label->setText("Не удалось открыть файл " + fileName);
        filePath = "";
        return;
    }
    if(!fileData.size())
    {
        qDebug() << "Файл " << fileName << " пуст.\n";
        return;
    } else
    {
        ParseData pd(fileData);

        if(pd.IsGoodData())
        {
            ui->label_3->setText(pd.GetParsedData()[0]);
            ui->lineEdit->setText(pd.GetParsedData()[1]);
            ui->label_4->setText(pd.GetParsedData()[2]);
            ui->lineEdit_4->setText(pd.GetParsedData()[3]);
            ui->lineEdit_5->setText(pd.GetParsedData()[4]);
        }
    }
}


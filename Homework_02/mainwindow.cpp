#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parseText = new ParseText();
    if (!parseText) close();


    QStringList listOfLang {"C++", "Python", "Java", "C#", "PHP", "JavaScript"};
    model = new QStandardItemModel(listOfLang.size(), 1, this);

    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex index = model->index(i, 0);
        QString str = listOfLang[i];
        model->setData(index, str, Qt::DisplayRole);
        model->setData(index, QIcon("./icons/" + str + ".png"), Qt::DecorationRole);
    }

    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::EditTrigger::DoubleClicked);
}

MainWindow::~MainWindow()
{
    if (parseText)
    {
        delete parseText;
        parseText = nullptr;
    }
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText();             // получаем текст виджета
    if (parseText->change(str))                                 // были ли выражения
    {
        ui->plainTextEdit->setPlainText(parseText->getText());  // заменяем текст примеры с результатами
        QTextCursor cur(ui->plainTextEdit->textCursor());
        cur.setPosition(ui->plainTextEdit->toPlainText().size());
        ui->plainTextEdit->setTextCursor(cur);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->listView->setViewMode(QListView::IconMode);
    } else
    {
        ui->listView->setViewMode(QListView::ListMode);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    model->insertRow(model->rowCount());
    QModelIndex index = model->index(model->rowCount() - 1, 0);
    model->setData(index, str, Qt::DisplayRole);
    model->setData(index, QIcon("./icons/Default.png"), Qt::DecorationRole);

    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->listView->selectionModel()->selectedIndexes().size())
    {
        model->removeRow(ui->listView->selectionModel()->selectedIndexes()[0].row());
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    int newRow = ui->listView->selectionModel()->selectedIndexes()[0].row();

    if(newRow != 0)
    {
        newRow = ui->listView->selectionModel()->selectedIndexes()[0].row() - 1;
    }

    QList<QStandardItem *> lst = model->takeRow(ui->listView->selectionModel()->selectedIndexes()[0].row());
    model->insertRow(newRow, lst);
    ui->listView->setCurrentIndex(model->index(newRow, ui->listView->selectionModel()->selectedIndexes()[0].column()));
}


void MainWindow::on_pushButton_4_clicked()
{
    int newRow = ui->listView->selectionModel()->selectedIndexes()[0].row();

    if(newRow < model->rowCount() - 1)
    {
        newRow = ui->listView->selectionModel()->selectedIndexes()[0].row() + 1;
    }

    QList<QStandardItem *> lst = model->takeRow(ui->listView->selectionModel()->selectedIndexes()[0].row());
    model->insertRow(newRow, lst);
    ui->listView->setCurrentIndex(model->index(newRow, ui->listView->currentIndex().column()));
}


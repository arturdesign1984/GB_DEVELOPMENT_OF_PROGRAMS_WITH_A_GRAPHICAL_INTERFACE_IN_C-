#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Calculate_clicked();

    void on_pushButtonAngle_clicked();



    void on_pushButtonAdd_clicked();

    void on_pushButtonReplaseText_clicked();

    void on_pushButtonAddHTML_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

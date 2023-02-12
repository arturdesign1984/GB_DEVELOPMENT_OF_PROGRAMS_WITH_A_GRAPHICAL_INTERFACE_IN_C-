#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork>
#include <QProgressBar>
#include <QMessageBox>
#include <QMutex>
#include "downloader.h"
#include "parsetext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
    void replyFinished(QNetworkReply* reply);
    void on_pushButton_clicked();
    void slotError();
    void slotDownloadProgress(qint64,qint64);
    void slotDone(const QUrl&, const QByteArray&);
    void on_pushButton_Go_clicked();

private:
    Ui::MainWindow *ui;
    Downloader *downloader;
    void showPic(const QString&);
    ParseText *parser;
    int selectLable = 0;
    QMutex mtx;
};

#endif // MAINWINDOW_H

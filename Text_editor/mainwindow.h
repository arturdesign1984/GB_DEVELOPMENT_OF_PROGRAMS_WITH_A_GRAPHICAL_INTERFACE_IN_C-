#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QAction>
#include <QFile>
#include <QTranslator>
#include <QKeyEvent>
#include <QShortcut>
#include <QMap>
#include <QDialog>
#include "navigatefilesysytem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void change_lang_to_en();
    void change_lang_to_ru();
    void on_actionInfo_triggered();
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_readonly_triggered();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();
    void on_actionWhite_triggered();
    void on_actionDark_triggered();

    void on_actionOpenPath_triggered(QString filePath);

private:

    NavigateFileSysytem *nfs;
    Ui::MainWindow *ui;
    QFile file;
    QTranslator translator;
    QDialog ChangeShortcut;
    QMap<QString, QAction*> shortcuts;
    void Shortcuts();
    void createConnactions();
    QString whiteTheme, darkTheme;
};
#endif // MAINWINDOW_H

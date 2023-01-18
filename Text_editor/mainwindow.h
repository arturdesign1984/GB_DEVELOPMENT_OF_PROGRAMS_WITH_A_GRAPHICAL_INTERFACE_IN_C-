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
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include "navigatefilesysytem.h"
#include "searchthread.h"

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

    void on_pushButton_Print_clicked();

    void randomColorsOfFont();
    void getCharFormat();

    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_setFont_clicked();

    void on_actionCopy_format_triggered();

    void on_actionPaste_format_triggered();

    void on_actionRandom_colors_Selected_triggered();

    void on_pushButton_Ins_Date_clicked();

    void on_pushButton_Ins_Time_clicked();

    void on_actionInsert_Date_triggered();

    void on_actionInsert_Time_triggered();

    void on_pushButton_5_clicked();

    void returnSearchPath(QString);

private:

    QTextCharFormat tcf;
    NavigateFileSysytem *nfs;
    Ui::MainWindow *ui;
    QFile file;
    QTranslator translator;
    QDialog ChangeShortcut;
    QMap<QString, QAction*> shortcuts;
    void Shortcuts();
    void createConnactions();
    QString whiteTheme, darkTheme;

    SearchThread* thread;
    QString path;
};
#endif // MAINWINDOW_H

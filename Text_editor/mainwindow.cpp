#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include <QTextCursor>
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QTranslator translator;
    if(translator.load(":/locales/Text_editor_ru_RU.qm"))
    {
        QCoreApplication::removeTranslator(&translator);
        QCoreApplication::installTranslator(&translator);
    }
    ui->setupUi(this);
    nfs = new NavigateFileSysytem(ui->widget);



    createConnactions();
    Shortcuts();

    whiteTheme = "QMenu, QMenu::item, QMenuBar { background-color: white; color: black }"
                 "QMainWindow, QLabel { background-color: #f3f3f3; color: black }"
                 "QTextEdit, QPushButton, QLineEdit, QComboBox { background-color: white; color: black }"
                 "QMenuBar::item:selected, QMenu::item:selected { background-color: lightblue }"
                 "QStatusBar { background-color: white; }"
                 "QLineEdit, QTextEdit { border: 2px solid lightgray; }"
                 "QComboBox QAbstractItemView, QWidget QTreeView, QScrollBar:vertical, QScrollBar:horizontal { border: 2px solid lightgray; background-color: white; color: black }";

    darkTheme = "QMenu, QMenu::item, QMenuBar { background-color: #333333; color: #dbdbdb }"
                "QMainWindow, QLabel { background-color: #232323; color: #cfbfad }"
                "QTextEdit, QPushButton, QLineEdit, QComboBox { background-color: #333333; color: #cfbfad }"
                "QMenuBar::item:selected, QMenu::item:selected { background-color: #265f99 }"
                "QStatusBar { background-color: #333333; }"
                "QLineEdit, QTextEdit { border: 2px solid #232323; }"
                "QComboBox QAbstractItemView, QWidget QTreeView, QScrollBar:vertical, QScrollBar:horizontal { border: 2px solid #232323; background-color: #333333; color: #dbdbdb }";

}

MainWindow::~MainWindow()
{
    delete ui;
    delete nfs;
}

void MainWindow::createConnactions()
{
    connect(ui->actionNew, &QAction::toggled, this, &MainWindow::on_actionNew_triggered);
    connect(ui->actionOpen, &QAction::toggled, this, &MainWindow::on_actionOpen_triggered);
    connect(ui->actionOpen_readonly, &QAction::toggled, this, &MainWindow::on_actionOpen_readonly_triggered);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::on_actionSave_as_triggered);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::on_actionSave_triggered);
    connect(ui->actionExit, &QAction::toggled, this, &MainWindow::on_actionExit_triggered);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_actionInfo_triggered);
    connect(ui->actionen_EN, &QAction::triggered, this, &MainWindow::change_lang_to_en);
    connect(ui->actionru_RU, &QAction::triggered, this, &MainWindow::change_lang_to_ru);
    connect(ui->actionWhite, &QAction::triggered, this, &MainWindow::on_actionWhite_triggered);
    connect(ui->actionDark, &QAction::triggered, this, &MainWindow::on_actionDark_triggered);

    connect(nfs, SIGNAL(on_file_doubleClicked(QString)), this, SLOT(on_actionOpenPath_triggered(QString)));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1)
    {
        on_actionInfo_triggered();
    }
}

void MainWindow::change_lang_to_en()
{
    if(translator.load(":/locales/Text_editor_en_EN.qm"))
    {
        QCoreApplication::removeTranslator(&translator);
        QCoreApplication::installTranslator(&translator);
    }
    ui->retranslateUi(this);
    Shortcuts();
}

void MainWindow::change_lang_to_ru()
{
    QTranslator translator;
    if(translator.load(":/locales/Text_editor_ru_RU.qm"))
    {
        QCoreApplication::removeTranslator(&translator);
        QCoreApplication::installTranslator(&translator);
    }
    ui->retranslateUi(this);
    Shortcuts();
}

void MainWindow::on_actionInfo_triggered()
{
    ui->textEdit->setReadOnly(true);

    file.setFileName(":/src/info.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(file.readAll());
        file.close();
    } else
    {
        qDebug() << tr("File info.txt lost") << ".\n";
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save file"),
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
        qDebug() << tr("Error when saving") << ".\n";
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(!file.isOpen() || file.fileName() != "")
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QString text = ui->textEdit->toPlainText();
            QByteArray ba = text.toUtf8();
            file.write(ba, ba.length());
            file.close();
        } else
        {
            on_actionSave_as_triggered();
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    ui->textEdit->setReadOnly(false);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    QDir::currentPath(),
                                                    "Text (*.txt);;All files (*.*)");

    file.setFileName(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(file.readAll());
        file.close();
    } else
    {
        qDebug() << tr("Failed to open file ") << fileName << ".\n";
    }
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->setReadOnly(false);
    file.setFileName("");
    ui->textEdit->setText("");
}

void MainWindow::on_actionExit_triggered()
{
    if(ui->textEdit->toPlainText() != "")
    {
        on_actionSave_triggered();
    }
    this->close();
}

void MainWindow::on_actionOpen_readonly_triggered()
{
    ui->textEdit->setReadOnly(true);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    QDir::currentPath(),
                                                    "Text (*.txt);;All files (*.*)");

    file.setFileName(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(file.readAll());
        file.close();
    } else
    {
        qDebug() << tr("Failed to open file ") << fileName << ".\n";
    }
}

void MainWindow::Shortcuts()
{
    shortcuts.clear();
    for(auto action : ui->menuFile->actions())
    {
        shortcuts.insert(action->text(), action);
    }
    for(auto action : ui->menuHelp->actions())
    {
        shortcuts.insert(action->text(), action);
    }
    ui->comboBox->clear();
    ui->comboBox->addItems(shortcuts.keys());
}

void MainWindow::on_comboBox_activated(int index)
{
    ui->lineEdit->setText(shortcuts.value(ui->comboBox->itemText(index))->shortcut().toString());
}

void MainWindow::on_pushButton_clicked()
{
    auto index = ui->comboBox->currentIndex();

    if(index != 0)
    {
        shortcuts[ui->comboBox->itemText(index)]->setShortcut(QKeySequence(ui->lineEdit->text()));
    }
}

void MainWindow::on_actionWhite_triggered()
{
    qApp->setStyleSheet(whiteTheme);
}


void MainWindow::on_actionDark_triggered()
{
    qApp->setStyleSheet(darkTheme);
}

void MainWindow::on_actionOpenPath_triggered(QString filePath)
{
    ui->textEdit->setReadOnly(false);

    file.setFileName(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(file.readAll());
        file.close();
    } else
    {
        qDebug() << tr("Failed to open file ") << filePath << ".\n";
    }
}

void MainWindow::on_pushButton_Print_clicked()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Print"));
    if (dlg.exec() != QDialog::Accepted)
    return;
    ui->textEdit->print(&printer);
}

void MainWindow::getCharFormat()
{
    tcf = ui->textEdit->textCursor().charFormat();
}

void MainWindow::randomColorsOfFont()
{
    std::srand(clock());
    QTextCharFormat textFormat;
    textFormat.setForeground(QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
    textFormat.setBackground(QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
    ui->textEdit->textCursor().setCharFormat(textFormat);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_setFont_clicked()
{
    QFont font = ui->textEdit->textCursor().charFormat().font();
    QFontDialog fontDlg(font,this);
    bool pressedOK = true;
    font = fontDlg.getFont(&pressedOK);
    if(pressedOK)
    {
        QTextCharFormat textFormat;
        textFormat.setFont(font);
        ui->textEdit->textCursor().setCharFormat(textFormat);
    }
}

void MainWindow::on_actionCopy_format_triggered()
{
    getCharFormat();
}

void MainWindow::on_actionPaste_format_triggered()
{
    ui->textEdit->textCursor().setCharFormat(tcf);
}

void MainWindow::on_actionRandom_colors_Selected_triggered()
{
    randomColorsOfFont();
}

void MainWindow::on_pushButton_Ins_Date_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(cursor);
    cursor.insertText(' ' + time.toString("dd.MM.yyyy") + ' ');
}

void MainWindow::on_pushButton_Ins_Time_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(cursor);
    cursor.insertText(' ' + time.toString("hh:mm:ss") + ' ');
}

void MainWindow::on_actionInsert_Date_triggered()
{
    QDateTime time = QDateTime::currentDateTime();
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(cursor);
    cursor.insertText(' ' + time.toString("dd.MM.yyyy") + ' ');
}


void MainWindow::on_actionInsert_Time_triggered()
{
    QDateTime time = QDateTime::currentDateTime();
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setTextCursor(cursor);
    cursor.insertText(' ' + time.toString("hh:mm:ss") + ' ');
}


void MainWindow::on_pushButton_5_clicked()
{
    QStringList fileNames = {ui->lineEdit_fileName->text()};
    path = QDir::cleanPath("/");
    QDir currentDir = QDir(path);
    thread = new SearchThread(fileNames, path, currentDir);
    connect(thread, SIGNAL(result(QString)), this, SLOT(returnSearchPath(QString)));
    thread->start();
}

void MainWindow::returnSearchPath(QString result)
{
    path = result;
    nfs->rebuildModel("C:" + path);
    delete thread;
}


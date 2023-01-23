#include "tascs.h"

Tascs::Tascs(QObject *parent) : QObject {parent}
{
    widget = new QWidget;
    open();
}

Tascs::~Tascs()
{
    save_as();
}

void Tascs::addTasc(QString newTasc)
{
    tascs += newTasc + '\n';
}


void Tascs::save_as()
{
    QString fileName = QFileDialog::getSaveFileName(widget,
                                                    "Сохранить",
                                                    QDir::currentPath(),
                                                    "Текст (*.txt);;Любой (*.*)");

    file.setFileName(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QString text = tascs;
        QByteArray ba = text.toUtf8();
        file.write(ba, ba.length());
        file.close();
    } else
    {
        qDebug() << "Error when saving" << ".\n";
    }
}

void Tascs::open()
{
    QString fileName = QFileDialog::getOpenFileName(widget,
                                                    "Open file",
                                                    QDir::currentPath(),
                                                    "Text (*.txt);;All files (*.*)");

    file.setFileName(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        tascs = (file.readAll());
        file.close();
    } else
    {
        qDebug() << "Failed to open file " << fileName << ".\n";
    }
}


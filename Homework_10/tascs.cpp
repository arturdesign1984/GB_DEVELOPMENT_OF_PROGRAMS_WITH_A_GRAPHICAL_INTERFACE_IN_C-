#include "tascs.h"

Tascs::Tascs(QObject *parent) : QObject {parent}
{
    numberOfTascs = 0;
    widget = new QWidget;
    file.setFileName(QDir::currentPath() + "\\lastUsed.bin");
    if(file.open(QIODevice::ReadOnly))
    {
        lastUsedFile = (file.readAll());
        file.close();
        file.setFileName(lastUsedFile);
        if(file.open(QIODevice::ReadOnly))
        {
            tascs = (file.readAll());
            file.close();
            for(auto i : tascs)
            {
                if(i == '\n')
                {
                    ++numberOfTascs;
                }
            }
        }
    }
}

Tascs::~Tascs()
{
    save();
    delete widget;
}

void Tascs::addTasc(QString newTasc)
{
    tascs += newTasc + '\n';
    ++numberOfTascs;
}

int Tascs::getTascsCount()
{
    return numberOfTascs;
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

        file.setFileName(QDir::currentPath() + "\\lastUsed.bin");
        if(file.open(QIODevice::WriteOnly))
        {
            ba = fileName.toUtf8();
            file.write(ba, ba.length());
            file.close();
        } else
        {
            qDebug() << "Error when saving last used file" << ".\n";
        }
    } else
    {
        qDebug() << "Error when saving" << ".\n";
    }
}

void Tascs::save()
{
    if(lastUsedFile == "")
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

            file.setFileName(QDir::currentPath() + "\\lastUsed.bin");
            if(file.open(QIODevice::WriteOnly))
            {
                ba = fileName.toUtf8();
                file.write(ba, ba.length());
                file.close();
            } else
            {
                qDebug() << "Error when saving last used file" << ".\n";
            }
        } else
        {
            qDebug() << "Error when saving" << ".\n";
        }
    } else
    {
        file.setFileName(lastUsedFile);
        if(file.open(QIODevice::WriteOnly))
        {
            QString text = tascs;
            QByteArray ba = text.toUtf8();
            file.write(ba, ba.length());
            file.close();
        } else
        {
            qDebug() << "Error when saving last used file" << ".\n";
        }
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
        lastUsedFile = fileName;
        numberOfTascs = 0;
        for(auto i : tascs)
        {
            if(i == '\n')
            {
                ++numberOfTascs;
            }
        }
    } else
    {
        qDebug() << "Failed to open file " << fileName << ".\n";
    }
}


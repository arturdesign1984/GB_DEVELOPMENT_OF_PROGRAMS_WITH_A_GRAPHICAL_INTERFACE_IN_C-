#pragma once
#ifndef PARSETEXT_H
#define PARSETEXT_H
#include <QString>
#include <QMap>

class ParseText
{
public:
    ParseText();
    bool parse(QString);
    QMap<int, QString> getUrlList();

private:
    QString preText;
    QMap<int,QString> urlList;
    QString value;
    int key;
    qint32 pos;         // Позиция указателя поиска
};

#endif // PARSETEXT_H

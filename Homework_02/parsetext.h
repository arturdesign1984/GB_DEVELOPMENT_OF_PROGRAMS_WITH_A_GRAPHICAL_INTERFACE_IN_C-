#pragma once
#ifndef PARSETEXT_H
#define PARSETEXT_H
#include <QString>
#include <QMap>

class ParseText
{
public:
    ParseText();
    bool change(QString);
    QString exchange(QString);
    QString getText();
private:
    QString text;       // Последний текст
    QString preText;    // Текст с правкой примера
    QMap<QString,QString> tegsList;   // Текст с тегами и символами
    QString key, value;
    qint32 pos;         // Позиция указателя поиска
};

#endif // PARSETEXT_H

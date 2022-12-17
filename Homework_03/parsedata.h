#ifndef PARSEDATA_H
#define PARSEDATA_H

#include <QRegularExpression>
#include <QDebug>

class ParseData
{
public:
    ParseData(QString&);
    bool IsGoodData();
    QStringList GetParsedData();

private:
    QString data;
    QStringList parsedData;
    bool isGoodData;
};

#endif // PARSEDATA_H

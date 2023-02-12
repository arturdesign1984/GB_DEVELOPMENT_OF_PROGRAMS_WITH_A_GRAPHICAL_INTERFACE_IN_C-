#include "parsetext.h"
#include <QRegularExpression>
#include <QDebug>

ParseText::ParseText()
{
    key = 0;
    value = "";
}

bool ParseText::parse(QString text)
{
    QRegularExpression regex1("(\"url\":\"https:)?(//[^\"'\\s]*[\\.]{1}jpg)");
//    QRegularExpression regex2("[а-я]+\\.");
    pos = 0;
    bool chg = false;
    preText = text;
    auto i = regex1.match(preText, pos);

    while(i.captured(0) != "")
    {
        urlList.insert(key, i.captured(0).right(i.captured(0).size() - 7));
        chg = true;
        key++;

        pos = preText.indexOf(i.captured(0), pos) + i.captured(0).size();
        i = regex1.match(preText, pos);
    }
    return chg;
}

QMap<int, QString> ParseText::getUrlList()
{
    return urlList;
}


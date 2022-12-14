#include "parsetext.h"
#include <QRegularExpression>
#include <QDebug>

ParseText::ParseText()
{
    text = "руб. ₽ #@RUB@ ₽ #@EUR@ € #@ALK@ ‰ #@COM@ © #@REG@ ® ";
    preText = "";
    key = "";
    value = "";
    QString::Iterator iter = text.begin();
    pos = 0;
    for (QString::Iterator i = text.begin(); i != text.end(); i++)
    {
        if (i->isSpace())
        {
            key = QString(iter, i - iter);
            value = *(i + 1);
            i += 2;
            iter = i + 1;
            tegsList.insert(key, value);
        }
    }
}

bool ParseText::change(QString istr)
{
    QRegularExpression regex1("#@[A-Z]+@");
    QRegularExpression regex2("[а-я]+\\.");
    pos = 0;
    bool chg = false;
    qint32 fnd = 0;
    preText = istr;
    auto i = regex1.match(preText, pos);

    while(i.captured(0) != "")
    {
        if (tegsList.contains(i.captured(0)))
        {
            fnd = preText.indexOf(i.captured(0), pos);
            preText.remove(fnd, i.captured(0).size());
            preText.insert(fnd, tegsList[i.captured(0)]);
            pos = fnd;
            chg = true;
            i = regex1.match(preText, pos);
            continue;
        }
        pos = preText.indexOf(i.captured(0), pos) + 2;
        i = regex1.match(preText, pos);
    }
    pos = 0;
    i = regex2.match(preText, pos);

    while(i.captured(0) != "")
    {
        if (tegsList.contains(i.captured(0)))
        {
            fnd = preText.indexOf(i.captured(0), pos);
            preText.remove(fnd, i.captured(0).size());
            preText.insert(fnd, tegsList[i.captured(0)]);
            pos = fnd;
            chg = true;
            i = regex2.match(preText, pos);
            continue;
        }
        pos = preText.indexOf('.', pos) + 1;
        i = regex2.match(preText, pos);
    }
    return chg;
}

QString ParseText::getText()
{
    return preText;
}

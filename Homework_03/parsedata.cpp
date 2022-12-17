#include "parsedata.h"

ParseData::ParseData(QString& str)
{
    data = str;
    isGoodData = false;

    QRegularExpression regex1("<a href=[^>]+/(?<currency>[A-Z]+)/[^>]+><img[^>]+>\\s?<div[^>]+><div class=\"rate__currency svelte-ov6yem\">(?<value>\\d+.\\d{1,2})</div>");
    QRegularExpression regex2("<span[^>]+data-testid=\"weather-temp\">([^<]+)</span>");

    auto resMoney = regex1.match(data, 0);

    for(int i = 0; i != -1; i = resMoney.capturedEnd())
    {
        parsedData.push_back(resMoney.captured("currency"));
        parsedData.push_back(resMoney.captured("value"));

        resMoney = regex1.match(data, resMoney.capturedEnd());
    }

    auto resWeather = regex2.match(data, 0);

    for(int i = 0; i != -1; i = resWeather.capturedEnd())
    {
        parsedData.push_back(resWeather.captured(1));
        qDebug() << resWeather.captured(1);

        resWeather = regex2.match(data, resWeather.capturedEnd());
    }
    if(parsedData.size() == 5)
    {
        isGoodData = true;
    }
    qDebug() << parsedData;
}

bool ParseData::IsGoodData()
{
    return isGoodData;
}

QStringList ParseData::GetParsedData()
{
    return parsedData;
}

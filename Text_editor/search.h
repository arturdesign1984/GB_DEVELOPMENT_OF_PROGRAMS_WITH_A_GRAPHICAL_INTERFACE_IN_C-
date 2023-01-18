#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>

class Search : public QObject
{
    Q_OBJECT
public:
    explicit Search(QObject *parent = nullptr);

signals:

};

#endif // SEARCH_H

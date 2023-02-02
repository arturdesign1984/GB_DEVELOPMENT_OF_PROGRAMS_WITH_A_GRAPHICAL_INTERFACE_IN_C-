#include "tascs.h"

Tascs::Tascs(QObject *parent) : QObject {parent}
{
    numberOfTascs = 0;
}

Tascs::~Tascs()
{
    delete widget;
}

void Tascs::addTasc(QString name, QString date, QString progress)
{
    tsv.AddRow(name, date, progress);
}

int Tascs::getTascsCount()
{
    return tsv.GetCount();
}

void Tascs::viewTascs()
{
    tsv.ViewTascs();
}

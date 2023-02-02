#ifndef TABLESQLVIEW_H
#define TABLESQLVIEW_H

#include <QWidget>
#include <QWindow>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>

class TableSQLView : public QWidget
{
    Q_OBJECT

public:
    explicit TableSQLView(QWidget *parent = nullptr);
    ~TableSQLView();
    bool ConnectDB();
    bool CreateTable();
    bool AddRow(QString name,QString date,QString progress);
    void ViewTascs();
    int GetCount();

signals:

private:
    QSqlDatabase db;
    QString currentTableName;
    QSqlQueryModel *model;
    QTableView *view;

};

#endif // TABLESQLVIEW_H

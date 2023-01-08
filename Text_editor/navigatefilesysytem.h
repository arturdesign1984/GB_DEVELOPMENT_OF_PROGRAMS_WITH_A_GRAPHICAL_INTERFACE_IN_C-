#ifndef NAVIGATEFILESYSYTEM_H
#define NAVIGATEFILESYSYTEM_H

#include <QWidget>
#include <QDir>
#include <QGridLayout>
#include <QTreeView>
#include <QLineEdit>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QApplication>

Q_PROPERTY(QFileSystemModel *model READ getCurrentModel WRITE setNewModel)

class NavigateFileSysytem : public QWidget
{
    Q_OBJECT

public:
    explicit NavigateFileSysytem(QWidget *parent = nullptr);
    void clearTree();

    QFileSystemModel *getCurrentModel()const
    {
        return model;
    }

    void setNewModel(QFileSystemModel *newmodel);
    void rebuildModel(QString str);

private:
    QGridLayout *gridLay;
    QTreeView *tree;
    QLineEdit *viewPath;

private slots:
    void chgDisk(int index);    // получаем индекс выбранного диска
    void goMainPath();          // Для UNIX-подобных ОС верхним уровнем является путь /
    void goToPath(QString str);            // Переходим на выбранную папку
    void on_tree_doubleClicked(const QModelIndex &index);

private:
    QFileSystemModel *model;
    QString curretnPath;

signals:
    void on_file_doubleClicked(QString filePath);
};

#endif // NAVIGATEFILESYSYTEM_H

#include "navigatefilesysytem.h"
#include <QModelIndex>
#include <QHeaderView>
#include <QScrollBar>

NavigateFileSysytem::NavigateFileSysytem(QWidget *parent)
    : QWidget{parent}, model(nullptr)
{
    gridLay = new QGridLayout(this);    // создаем слой для компоновки
    this->setLayout(gridLay);   // устанавливаем слой на виджет
    tree = new QTreeView(this);
    tree->horizontalScrollBar()->setEnabled(true);
    viewPath = new QLineEdit(this);
    gridLay->addWidget(viewPath,
                       0,
                       0,
                       1,
                       10
                       );
    gridLay->addWidget(tree,
                       1,       // размещен на первой строке
                       0,       // с нулевого столбца
                       10,      // занимает 10 условных строк
                       10       // и 10 столбцов
                       );

    setMinimumSize(200, 400);   // ограничиваем размер виджета

    model = new QFileSystemModel(this);
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);
    model->setRootPath("");

    connect(tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tree_doubleClicked(QModelIndex)));
    rebuildModel("/");

    tree->setColumnHidden(1, true);
    tree->setColumnHidden(2, true);
    tree->setColumnHidden(3, true);

    tree->setHeaderHidden(true);
}

void NavigateFileSysytem::chgDisk(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void NavigateFileSysytem::goMainPath()
{
    rebuildModel("/");
}

void NavigateFileSysytem::goToPath(QString str)
{
    rebuildModel(str);
}

void NavigateFileSysytem::on_tree_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);
    QDir dir = fileInfo.dir();
    if(fileInfo.isDir())
    {
        viewPath->setText(dir.absolutePath() + fileInfo.fileName());
    }
    if(fileInfo.isFile())
    {
        viewPath->setText(dir.absolutePath());
        emit on_file_doubleClicked(viewPath->text() + '/' + fileInfo.fileName());
    }
}

void NavigateFileSysytem::setNewModel(QFileSystemModel *newmodel)
{
    tree->setModel(newmodel);
    model = newmodel;
}

void NavigateFileSysytem::rebuildModel(QString str)
{
    curretnPath = str;
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);
    model->setRootPath("");
    setNewModel(model);
}


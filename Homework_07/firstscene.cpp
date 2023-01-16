#include "firstscene.h"

FirstScene::FirstScene(QObject *parent) : QGraphicsScene(parent)
{
    this->setSceneRect(0,0,800,600);
    currentGeometry = BlockScheme::Geometry::RECTANGLE;
}

void FirstScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !this->itemAt(event->scenePos(), {}))
    {
        graphicsItem = new BlockScheme(this);
        graphicsItem->setGeometry(currentGeometry);
        graphicsItem->setPos(event->scenePos() - graphicsItem->getBoundingRectCenter());
        this->addItem(graphicsItem);

        this->update();

        if (currentGeometry == BlockScheme::Geometry::STAR)
        {
            currentGeometry = BlockScheme::Geometry::RECTANGLE;
        }
        else if (currentGeometry == BlockScheme::Geometry::RECTANGLE)
        {
            currentGeometry = BlockScheme::Geometry::ELLIPS;
        }
        else
        {
            currentGeometry = BlockScheme::Geometry::STAR;
        }
    }

    if (event->button() == Qt::RightButton && this->itemAt(event->scenePos(), {}))
    {
        QGraphicsItem* pCurrentItem = this->itemAt(event->scenePos(),{});
        this->removeItem(pCurrentItem);
    }

    QGraphicsScene::mousePressEvent(event);
}

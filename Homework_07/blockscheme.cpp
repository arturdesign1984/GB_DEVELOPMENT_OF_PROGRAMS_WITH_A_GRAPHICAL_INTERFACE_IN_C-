#include "blockscheme.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

BlockScheme::BlockScheme(QObject *parent) : QObject(parent), QGraphicsItem()
{
    srand(clock());
    x = 0;
    y = 0;
    brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать
    geometry = Geometry::RECTANGLE; // По умолчанию - прямоугольник
    setPos(0,0);
}

void BlockScheme::setGeometry(Geometry geom)
{
    geometry = geom;
}

QPointF BlockScheme::getBoundingRectCenter()
{
    return this->boundingRect().center();
}

void BlockScheme::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    QPolygon star;
    star << QPoint(x+0, y+85) << QPoint(x+75, y+75)
         << QPoint(x+100, y+10) << QPoint(x+125, y+75)
         << QPoint(x+200, y+85) << QPoint(x+150, y+125)
         << QPoint(x+160, y+190) << QPoint(x+100, y+150)
         << QPoint(x+40, y+190) << QPoint(x+50, y+125)
         << QPoint(x+0, y+85);

    if (geometry == Geometry::ELLIPS)
    {
        painter->drawEllipse(x, y, 200, 100);
    }
    if (geometry == Geometry::RECTANGLE)
    {
        painter->drawRect(x, y, 200, 100);
    }
    if (geometry == Geometry::STAR)
    {
        painter->drawPolygon(star);
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF BlockScheme::boundingRect() const
{
    if(geometry == Geometry::STAR)
    {
        return QRectF(x, y, 200, 200);
    }
    return QRectF(x, y, 200, 100);

}

void BlockScheme::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);

}

void BlockScheme::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void BlockScheme::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos() - this->boundingRect().center()));
}



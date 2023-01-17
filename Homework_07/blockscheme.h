#ifndef BLOCKSCHEME_H
#define BLOCKSCHEME_H

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QCursor>

class BlockScheme : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    enum Geometry {RECTANGLE, ELLIPS, STAR};
    explicit BlockScheme(QObject *parent = nullptr);
    void setGeometry(Geometry geom);
    QPointF getBoundingRectCenter();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    bool rotate = false;
    int x, y;
    Geometry geometry;
    QPoint bpoint;
    QBrush brush;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BLOCKSCHEME_H

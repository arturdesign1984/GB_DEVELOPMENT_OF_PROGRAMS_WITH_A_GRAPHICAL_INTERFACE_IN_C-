#ifndef FIRSTSCENE_H
#define FIRSTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include "blockscheme.h"

class FirstScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit FirstScene(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    BlockScheme* graphicsItem;
    BlockScheme::Geometry currentGeometry;

};

#endif // FIRSTSCENE_H

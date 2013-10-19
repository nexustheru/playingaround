#include "myscene.h"
QGraphicsItem * mousitem;
QList<QGraphicsItem *> notundermouse;

myscene::myscene(QObject *parent) :
    QGraphicsScene(parent)
{

}

void myscene::advance()
{

}


void myscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mouseMoveEvent(event);
}

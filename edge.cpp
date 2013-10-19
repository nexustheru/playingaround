#include <QPainter>

#include "edge.h"
#include "node.h"

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

Edge::Edge(Node *sourceNode, Node *destNode)
    : arrowSize(10)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;
    qreal sx=source->scenePos().x()/2;
    qreal sy=source->scenePos().y();
    qreal dx=dest->scenePos().x()/2;
    qreal dy=dest->scenePos().y();
    QLineF line(source->scenePos(),dest->scenePos());
    qreal length = line.length();

    prepareGeometryChange();
    //setLine(QLineF(myFromNode->pos(), myToNode->pos()));

        sourcePoint = line.p1 ();
        destPoint = line.p2 ();

}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized();

}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::lightGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);


}
QPair<qreal, qreal> Edge::getMidPoint()
{
    //this function calculates the mid point of
    //the link, using position of nodes
    //math rulez, bro! :D
    qreal minX=source->x()<dest->x()?source->x():dest->x();
    qreal minY=source->y()<dest->y()?source->y():dest->y();
    qreal midX=((dest->x()-source->x())/2)+minX;
    qreal midY=((dest->y()-source->y())/2)+minY;
    return QPair<qreal, qreal>(midX, midY);
}


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QStaticText>
#include <QInputDialog>
#include <QLineEdit>
#include <QFontMetrics>
#include <QGradient>
#include "edge.h"
#include "node.h"
#include <mainwindow.h>
QString fname=NULL;


Node::Node()
{
    setFlag(ItemIsMovable,true);
    setFlag(ItemIsSelectable,true);
    setFlag(ItemSendsGeometryChanges,true);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    im.load("icons/node.tga",0);

}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    QFontMetrics metrics(myText);
    int pixelWidth = metrics.width(myText);
    return QRectF(0,0,pixelWidth,20);

}
void Node::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    fname=text;
    update();
}


QString Node::returntypename()
{
    return myText;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(QPen(Qt::black, 0));
    QLinearGradient gradient(0, 0, 0,boundingRect().height()-1);
         gradient.setColorAt(0.0, Qt::white);
         gradient.setColorAt(0.2, QColor(200, 200, 255));
         gradient.setColorAt(0.8, QColor(200, 200, 255));
         gradient.setColorAt(1.0, QColor(127, 127, 200));
     painter->setBrush(QBrush(gradient));
    //painter->setBrush(QBrush("#cbd4e1"));
    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(),Qt::AlignCenter | Qt::TextSelectableByMouse ,myText);

}

void Node::nodename(QString sname)
{
    fname=sname;

}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();

        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString text = QInputDialog::getText(event->widget(),
                               "Edit Text","Enter new text:",
                               QLineEdit::Normal, myText);
        if (!text.isEmpty())
            setText(text);
}


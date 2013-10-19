#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QStaticText>
#include <QInputDialog>
#include <QLineEdit>
#include <QFontMetrics>
#include <QGradient>
#include "mte.h"
QString fnameg=NULL;


mte::mte()
{
    setFlag(ItemIsMovable,true);
    setFlag(ItemIsSelectable,true);
}


QRectF mte::boundingRect() const
{
    QFontMetrics metrics(myText);
    int pixelWidth = metrics.width(myText);
    return QRectF(0,0,pixelWidth,50);

}
void mte::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    fnameg=text;
    update();
}


QString mte::returntypename()
{
    return myText;
}

void mte::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{

    painter->setPen(QPen(Qt::black, 0));
    //painter->setBrush(QBrush("#cbd4e1"));
    //painter->drawRect(boundingRect());
    painter->drawText(boundingRect(),Qt::AlignCenter,myText);
}

QVariant mte::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return value;
}

void mte::nodename(QString sname)
{
    fnameg=sname;

}

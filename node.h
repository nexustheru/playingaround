#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <QImage>
#include <QPixmap>
#include <QMenu>

class Edge;
class MainWindow;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Node : public QObject,public QGraphicsItem
{
     Q_OBJECT
public:
    Node();
    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void static nodename(QString sname);
    void setText(const QString &text);

    QString returntypename(void);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    MainWindow *graph;
    QPixmap pix;
    QImage im;
   QString myText;
   QString thisnodetype;


};


#endif

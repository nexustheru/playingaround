#ifndef MTE_H
#define MTE_H

#include <QGraphicsItem>
#include <QList>
#include <QImage>
#include <QPixmap>
#include <QMenu>

class MainWindow;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class mte : public QObject,public QGraphicsItem
{
     Q_OBJECT
public:
    mte();
    QRectF boundingRect() const;
    void static nodename(QString sname);
    void setText(const QString &text);
    QString returntypename(void);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:

public slots:

private:

   QString myText;
   QString thisnodetype;


};


#endif

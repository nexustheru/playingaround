#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <node.h>

class myscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myscene(QObject *parent = 0);

signals:
    
public slots:
   void advance();
public:


protected:
virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

 private:
     qreal angle;
     qreal speed;
     qreal mouseEyeDirection;
     Node* nod;

};

#endif // MYSCENE_H

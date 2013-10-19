#ifndef QVIEW_H
#define QVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDrag>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGraphicsSceneEvent>
#include <QGraphicsScene>
#include <QtGui>
#include <node.h>

class qview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit qview(QWidget *parent = 0);

protected:
       virtual void dragEnterEvent ( QDragEnterEvent * event );
       virtual void dragLeaveEvent ( QDragLeaveEvent * event );
       virtual void dragMoveEvent ( QDragMoveEvent * event );
       virtual void dropEvent ( QDropEvent * event );

signals:
    
public slots:

private:
    std::string tempname;
    Node* nnode;
};

#endif // QVIEW_H

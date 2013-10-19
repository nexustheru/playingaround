#include "qview.h"

qview::qview(QWidget *parent) :
    QGraphicsView(parent)
{

   setAcceptDrops(true);

}

void qview::dragEnterEvent(QDragEnterEvent *event)
{

    event->accept();

}

void qview::dragLeaveEvent(QDragLeaveEvent *event)
{

    event->accept();

}

void qview::dropEvent(QDropEvent *event)
{

    if(event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")==true)
    {
        QByteArray encoded_data =event->mimeData()->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encoded_data, QIODevice::ReadOnly);
        QMap<int, QVariant> v;
        int r, c;
        while (!stream.atEnd())
        {
        stream >> r >> c >> v;
        }
        nnode=new Node();
        nnode->setText(v[0].toString());
        scene()->addItem(nnode);
    }
    else
    {
        nnode=new Node();
        nnode->setText("NiObject");
        scene()->addItem(nnode);
    }

    event->accept();
    QGraphicsView::dropEvent(event);
}
void qview::dragMoveEvent(QDragMoveEvent *event)

{

    event->accept();

}

#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsScene>
#include <QTreeWidget>
#include <QDataStream>
#include <QFileInfo>
#include <bsa.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //setMouseTracking(true);

    connect(&time,SIGNAL(timeout()),this,SLOT(update()));
    connect(ui->actionAdd_Node,SIGNAL(triggered()),this,SLOT(addnode()));
    //connect(ui->actionLoad_nif_xml,SIGNAL(triggered()),this,SLOT(setdoom()));
    connect(ui->actionAdd_node_from_selected,SIGNAL(triggered()),this,SLOT(addnodesel()));
    connect(ui->actionAdd_Link,SIGNAL(triggered()),this,SLOT(addlink()));
    connect(ui->actionOpenfile,SIGNAL(triggered()),this,SLOT(openfile()));
    connect(ui->actionSave_file,SIGNAL(triggered()),this,SLOT(savefile()));
    connect(ui->actionDelete_selected,SIGNAL(triggered()),this,SLOT(del()));
    connect(ui->actionClear_all_selection_in_lists,SIGNAL(triggered()),this,SLOT(clearsele()));
    connect(ui->treeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(settex()));
    time.start(10);
    scene=new myscene();
     ui->graphicsView->setScene(scene);
     ui->treeWidget->setDragEnabled(true);
     ui->treeWidget->viewport()->setAcceptDrops(true);
     ui->treeWidget->setDropIndicatorShown(true);
     pixi.load("icons/node.tga",0,Qt::AutoColor);
     ic.addPixmap(pixi);
     load_nifliblist();
     ui->graphicsView->setAcceptDrops(true);

     setAcceptDrops(true);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addnode()
{
    if(ui->treeWidget->selectedItems().count() > 0)
        {
            nod=new Node();
            nod->setText(ui->treeWidget->selectedItems()[0]->text(0));
            scene->addItem(nod);
        }
        else if(ui->treeWidget->selectedItems().empty()==true)
        {
            nod=new Node();
            nod->setText("NiObject");
            scene->addItem(nod);
        }
        else
        {
            nod=new Node();
            nod->setText("NiObject");
            scene->addItem(nod);
        }
}

void MainWindow::addnodesel()
{
    if(ui->listWidget->selectedItems()[0]->text().count() > 0)
    {
        nod=new Node();
        nod->setText(ui->listWidget->selectedItems()[0]->text());
        scene->addItem(nod);
    }
    else
    {
        nod=new Node();
        nod->setText("NiObject");
        scene->addItem(nod);
    }
setdoom();
}

void MainWindow::addlink()
{

    int co=scene->selectedItems().count();
    for(int i=0;i < co;i++)
    {
        nod=new Node();
        nod1=new Node();
        scene->selectedItems()[i]->children().append(scene->selectedItems()[i+1]);
        nod=static_cast<Node*>(scene->selectedItems()[i]);
        nod1=static_cast<Node*>(scene->selectedItems()[i+1]);
        qDebug("nod");
        ed=new Edge(nod,nod1);
        scene->addItem(ed);
        i=2;

    }

}

void MainWindow::havokfilehkx(std::string filename)
{
    qDebug(filename.c_str());
    hkIstream stream(filename.c_str());
    resource = hkSerializeUtil::load(stream.getStreamReader());
    root=resource->getContents<hkRootLevelContainer>();
    ragg =reinterpret_cast<hkaRagdollInstance*>(root->findObjectByType(hkaRagdollInstanceClass.getName()));
    skel =reinterpret_cast<hkaSkeleton*>(root->findObjectByType(hkaSkeletonClass.getName()));
    const hkArray<hkpRigidBody*>& riggarray=ragg->getRigidBodyArray();
    for(int i=0 ;i < riggarray.getSize();i++)
    {
        rigidbody=riggarray[i];
        hkrigids.append(rigidbody);
    }

}

QString inttoqs(unsigned long value)
{
    string temp=QString::number(value).toStdString();
    QString val=QString::fromStdString(temp);
    return val;
}

void MainWindow::bsafile(string filename)
{
    try
    {
     open_bsa(filename.c_str(),ui->treeWidget_2);
    }
    catch(...)
    {
        qDebug("Exception") ;
    }


}

void MainWindow::nifilesave(string filename)
{
    using namespace Niflib;
    ofstream out(filename.c_str(), ofstream::binary );
    NifInfo nifInfo(VER_20_2_0_7, 12, 83);
    QStringList items;
    items << tr("Filetree") << tr("Graphview");
    QString text = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                               tr("List Select"), items, 0, false, 0);

    int co=scene->selectedItems().size();
    for(int i=0;i < co;i++)
    {
        QGraphicsItem* ite=scene->items()[i];
        qDebug("ite->.toStdString().c_str()");

    }

      //WriteNifTree(out,nifavobjects[0],nifInfo);

}

void MainWindow::havokfilexml(std::string filename)
{
    qDebug(filename.c_str());
    hkIstream stream(filename.c_str());
    resource = hkSerializeUtil::load(stream.getStreamReader());
    root=resource->getContents<hkRootLevelContainer>();
    ragg =reinterpret_cast<hkaRagdollInstance*>(root->findObjectByType(hkaRagdollInstanceClass.getName()));
    skel =reinterpret_cast<hkaSkeleton*>(root->findObjectByType(hkaSkeletonClass.getName()));
    const hkArray<hkpRigidBody*>& riggarray=ragg->getRigidBodyArray();
    for(int i=0 ;i < riggarray.getSize();i++)
    {
        rigidbody=riggarray[i];
        hkrigids.append(rigidbody);
    }

}

void MainWindow::filllist(void)
{
vector<string> typnames;
    for(unsigned int i=0 ;i < nifobjects.size();i++)
    {
        NiObjectRef obj=nifobjects[i];
        typnames.push_back(obj->GetType().GetTypeName());
        QString str=QString::fromStdString(obj->asString(true));
        QStringList li=str.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
        content.push_back(li);
    }
    QTreeWidgetItem* rootitem=new QTreeWidgetItem();
    rootitem->setText(0,"Nif");
    for(int f=0 ;f < content.size();f++)
    {
       QTreeWidgetItem* child=new QTreeWidgetItem();
       child->setIcon(0,QIcon("icons/nodeP.tga"));
       child->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
       child->setText(0,"NiObject");
       for(int p=0 ;p < content[f].size();p++)
       {
           QTreeWidgetItem* subchild=new QTreeWidgetItem();
           subchild->setIcon(0,QIcon("icons/nodeP.tga"));
           subchild->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
           subchild->setText(0,content[f].at(p));
           child->addChild(subchild);
       }
       rootitem->addChild(child);
    }
    for(unsigned int o=0; o < typnames.size();o++)
    {
        rootitem->child(o)->setText(0,QString::fromStdString(typnames[o]));
        rootitem->child(o)->setIcon(0,QIcon("icons/node.tga"));
    }
   ui->treeWidget->insertTopLevelItem(0,rootitem);
   rootitem->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);

}


void MainWindow::treeview()
{

}

void MainWindow::load_nifliblist()
{
    string sLine = "";
     ifstream infile;

     infile.open("niflib.txt");

     while (!infile.eof())
     {
     getline(infile, sLine);
     ui->listWidget->insertItem(0,sLine.c_str());
     }

     infile.close();

}

void MainWindow::rec(QDomNode nod)
{
    for(int i=0 ;i < nod.childNodes().count();i++)
    {
        if(nod.childNodes().at(i).isComment()==false)
        {
            QTreeWidgetItem* xitem=new QTreeWidgetItem();
            xitem->setText(0,nod.childNodes().at(i).nodeName());
            ui->treeWidget_2->insertTopLevelItem(0,xitem);
            QDomNode chi=nod.childNodes().at(i);
            rec(chi);
        }


    }

}

void MainWindow::setdoom()
{
    file=new QFile("nif.xml");
    QDomDocument doc;

    doc.setContent(file,false, &errorStr, &errorLine,&errorColumn);
    QDomElement root = doc.documentElement();
    rec(root.toElement());

    //xroot = xroot.nextSibling();

}

void MainWindow::nif(std::string filename)
{
 using namespace Niflib;
    ifstream in(filename.c_str(), ifstream::binary );
    nifobjects = ReadNifList(filename);
    nnode=DynamicCast<NiNode>(nifobjects[0]);
    nifavobjects=nnode->GetChildren();
    qDebug(nnode->GetName().c_str());
    filllist();
}

void MainWindow::processfile(QString filename)
{
    QFileInfo inf(filename);
    std::string siff=inf.suffix().toStdString();
    if(siff=="nif")
    {
        nif(filename.toStdString());
    }
    else if(siff=="xml")
    {
        havokfilexml(filename.toStdString());

    }
    else if(siff=="hkx")
    {
        havokfilehkx(filename.toStdString());
    }
    else if(siff=="bsa")
    {
        bsafile(filename.toStdString());
    }
    else
    {
        qDebug("file is of uknown format");
    }
}

void MainWindow::uprocessfile(QString filename)
{
    QFileInfo inf(filename);
    std::string siff=inf.suffix().toStdString();
    if(siff=="nif")
    {
      nifilesave(filename.toStdString());
    }
    else if(siff=="xml")
    {


    }
    else if(siff=="hkx")
    {

    }
    else
    {
        qDebug("file is of uknown format");
    }
}

void MainWindow::openfile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home/jana", tr("Files (*.hkx *.nif *.xml *.* *.bsa)"));
    processfile(fileName);
}

void MainWindow::savefile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/home/jana", tr("Files (*.hkx *.nif *.xml *.*)"));
    uprocessfile(fileName);
}

void MainWindow::settex()
{
    for( int j=0; j < ui->tableWidget->columnCount();j++)
    {
        ui->tableWidget->removeColumn(j);
    }
    ui->tableWidget->removeRow(0);

    ui->tableWidget->setRowCount(0);
    QString item=ui->treeWidget->selectedItems()[0]->text(0);
    item.replace("(","",Qt::CaseInsensitive);
    item.replace(")","",Qt::CaseInsensitive);
    QStringList list;
    QRegExp rx( ":|," );
    if(item.contains(rx)==true)
    {
        list=item.split(rx);
    }
    ui->tableWidget->setColumnCount(list.size()-1);
    ui->tableWidget->insertRow(0);

    for(int i=0;i < list.size();i++)
    {
        ui->tableWidget->insertColumn(i);
        QTableWidgetItem* ite=new QTableWidgetItem();
        ite->setText(list[i]);
        ui->tableWidget->setItem(0,i,ite);
    }
}

void MainWindow::del()
{
        QList<QGraphicsItem *> items = scene->selectedItems();
        QMutableListIterator<QGraphicsItem *> i(items);
        while (i.hasNext()) {
            Edge *edge = dynamic_cast<Edge *>(i.next());
            if (edge) {
                delete edge;
                i.remove();
            }
        }

        qDeleteAll(items);
}

void MainWindow::clearsele()
{
    ui->treeWidget->clearSelection();
    ui->listWidget->clearSelection();
}

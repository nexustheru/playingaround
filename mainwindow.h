#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <node.h>
#include <mte.h>
#include "edge.h"
#include <math.h>
#include <QTimer>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtXml/QDomAttr>
#include <QtXml/QDomDocument>
#include <QFile>
#include <iostream>
#include <QDebug>
#include <QIODevice>
#include <QFileDialog>
#include <includesnif.h>
#include <includeshav.h>
#include <QVector>
#include <templates.h>
#include <myscene.h>
#include <QListWidget>
#include <QInputDialog>
#include <QContextMenuEvent>
#include <zlib.h>


using namespace Niflib;

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void processfile(QString filename);
    void uprocessfile(QString filename);
    void havokfilexml(std::string filename);
    void havokfilehkx(std::string filename);
    void bsafile(std::string filename);
    void nifilesave(std::string filename);
    void nif(std::string filename);
    void filllist(void);
    void treeview(void);
    void load_nifliblist(void);
    void rec(QDomNode nod);

    ~MainWindow();
public slots:
    void addnode(void);
    void addnodesel(void);
    void addlink(void);
    void openfile(void);
    void savefile(void);
    void settex(void);
    void del(void);
    void clearsele(void);
    void setdoom(void);
    void unpackselecteddata(void);
signals:

private:
    Ui::MainWindow *ui;
    myscene* scene;
    Node* nod;
    Node* nod1;
    Edge* ed;
    int timerId;
    QTimer time;
    hkRootLevelContainer* root;
    hkpRigidBody* rigidbody;
    hkpRigidBodyCinfo* cinfo;
    QVector<hkpRigidBody*> hkrigids;
    QVector<hkaBone> hkbones;
    hkaRagdollInstance* ragg;
    hkaSkeleton* skel;
    hkResource* resource ;
    vector<NiObjectRef> nifobjects;
    vector<NiAVObjectRef> nifavobjects;
    QVector<QStringList> content;
    Niflib::NiNodeRef nnode;
    QPixmap pixi;
    QIcon ic;
    QString errorStr;
    int errorLine;
    int errorColumn;
    QFile* file;
    Niflib::ObjectRegistry* reg;
    mte* qm;


};

#endif // MAINWINDOW_H

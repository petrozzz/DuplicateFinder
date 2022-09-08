#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "pathdiscobject.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    pathDisc = new PathDiscObject("..", "");
    //pathDisc->calcDiscObject();
    init_treewidget();
}

MainWindow::~MainWindow(){
    delete pathDisc;
    pathDisc = nullptr;
    delete ui;
}

void MainWindow::init_treewidget(){
    QStringList lst;
    lst << "Folders" << "Used space";
    ui->treeWidget->setHeaderLabels(lst);
    ui->treeWidget->setSortingEnabled(true);

    QTreeWidgetItem* pTWItem = new QTreeWidgetItem(ui->treeWidget);
    pTWItem->setText(0, "Local Disk");
    std::list<DiscObject> discs = pathDisc->getDiscObjects();
    for(std::list<DiscObject>::iterator obj = discs.begin() ; obj != discs.end(); obj++){
        QTreeWidgetItem* pTWItem2 = new QTreeWidgetItem(pTWItem);        
        pTWItem2->setText(0, QString((*obj).getName().data()));
        pTWItem2->setText(1, (*obj).do_type.data());
        if((*obj).do_type.compare("Dir") == 0)
            show_path(pTWItem2, &(*obj))
        ;
    }
    pTWItem->setExpanded(true);
    ui->treeWidget->repaint();
}

void MainWindow::show_path( QTreeWidgetItem *pTWItem3, DiscObject *pathDisc){
    PathDiscObject dd(pathDisc->getRoot(), pathDisc->getName());
    std::list<DiscObject> discs = dd.getDiscObjects();
    for(std::list<DiscObject>::iterator obj = discs.begin() ; obj != discs.end(); obj++){
        QTreeWidgetItem* pTWItem4 = new QTreeWidgetItem(pTWItem3);
        pTWItem4->setText(0, QString((*obj).getName().data()));
        pTWItem4->setText(1, (*obj).do_type.data());
        if((*obj).do_type.compare("Dir")==0)
            show_path(pTWItem4, &(*obj));
    }
}






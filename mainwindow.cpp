#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
/*
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
*/
#include "pathdiscobject.h"
#include "filediscobject.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , countGroup{0}{
    ui->setupUi(this);
    load_settings();
    pathDisc = new PathDiscObject(str_pathDisc, "");
    //pathDisc->calcDiscObject();
    init_treewidget();
}

MainWindow::~MainWindow(){
    //delete pathDisc;
    //pathDisc = nullptr;
    delete ui;
}

void MainWindow::init_treewidget(){
    QStringList lst;
    lst << "Folders" << "Type" << "Used space" << "Create time" << "Modified time" << "Group";
    ui->treeWidget->setHeaderLabels(lst);
    ui->treeWidget->setSortingEnabled(true);
    ui->treeWidget->setColumnWidth(0, 300);
    ui->treeWidget->setColumnWidth(1, 50);

    QTreeWidgetItem* pTWItem = new QTreeWidgetItem(ui->treeWidget);
    pTWItem->setText(0, "Local Disk");
    std::list<DiscObject> discs = pathDisc->getDiscObjects();

    std::list<FileDiscObject> all_files;

    duplicate_files.clear();
    all_files.clear();
    pathDisc->getAllFiles(all_files);
    setGroup(all_files, duplicate_files);

    for(std::list<DiscObject>::iterator obj = discs.begin() ; obj != discs.end(); obj++){
        QTreeWidgetItem* pTWItem2 = new QTreeWidgetItem(pTWItem);
        pTWItem2->setText(0, QString((*obj).getName().data()));
        pTWItem2->setText(1, (*obj).do_type.data());
        if((*obj).do_type.compare("Dir") == 0)
            show_path(pTWItem2, &(*obj));
        /*else*/ {
            pTWItem2->setText(2, QString::number((*obj).getSize()));
            pTWItem2->setText(3, (*obj).getCreateTime().data());
            pTWItem2->setText(4, (*obj).getModifiedTime().data());
            if(duplicate_files.find((*obj).getRoot() + "/" + (*obj).getName()) != duplicate_files.end())
                pTWItem2->setText(5, QString::number(duplicate_files[(*obj).getRoot() + "/" + (*obj).getName()]));
        }
    }
    pTWItem->setExpanded(true);    
    ui->treeWidget->repaint();
}

void MainWindow::load_settings()
{
    std::ifstream in("setting.ini");
    std::string str;
    if (in.is_open()) {
       while (getline(in, str)){
           int pos = (int)str.find('=');
           if(pos >= 0){
              std::string st2 = str.substr(pos+1);
              if(str.substr(0, pos) == "title"){
                  setWindowTitle(st2.data());
              }
              else if(str.substr(0, pos) == "path"){
                  str_pathDisc = st2;
              }
           }
       }
       in.close();
    }
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
        /*else*/{
            pTWItem4->setText(2, QString::number((*obj).getSize()));
            pTWItem4->setText(3, (*obj).getCreateTime().data());
            pTWItem4->setText(4, (*obj).getModifiedTime().data());
            if(duplicate_files.find((*obj).getRoot() + "/" + (*obj).getName()) != duplicate_files.end())
                pTWItem4->setText(5, QString::number(duplicate_files[(*obj).getRoot() + "/" + (*obj).getName()]));
        }
    }
}






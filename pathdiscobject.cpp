#include "pathdiscobject.h"
#include "filediscobject.h"
#include <iostream>

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

using namespace std;

PathDiscObject::PathDiscObject(){
}

PathDiscObject::PathDiscObject(std::string root, std::string name):DiscObject(root, name){
    calcDiscObject();
}

DiscObjectType PathDiscObject::get_type(){
    return DiscObjectType::PathObject;
}

void PathDiscObject::calcDiscObject()
{
    QString dirPath = (this->getRoot() + this->getName()).data();
    //QStringList fileNameFilters;
    //fileNameFilters.clear();
    //fileNameFilters.push_back("*.*");
    QStringList fileNameList;
    fileNameList << QDir(dirPath).entryList(/*fileNameFilters, */QDir::Files | QDir::Hidden);
    QFileInfo fileInfo;
    foreach (const QString& fileName, fileNameList)    {
        discobjects.push_back((DiscObject)(FileDiscObject(dirPath.toStdString(),fileName.toStdString())));
        (discobjects.back()).do_type = "File";
    }
    QStringList subDirNameList;
    subDirNameList << QDir(dirPath).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach (const QString& subDirName, subDirNameList)    {
        QString fullPath = dirPath + QDir::separator() + subDirName;
        discobjects.push_back((DiscObject)(PathDiscObject(dirPath.toStdString()+"/",subDirName.toStdString())));
        (discobjects.back()).do_type = "Dir";
    }
}

void PathDiscObject::getAllFiles(std::list<FileDiscObject> &all_files){

    auto it = discobjects.begin();
    while(it != discobjects.end()){
        if((*it).do_type.compare("Dir") == 0){
            PathDiscObject dobj((*it).getRoot(), (*it).getName());
            dobj.getAllFiles(all_files);
        } else {
            all_files.push_back(FileDiscObject((*it).getRoot(), (*it).getName()));
        }
        it++;
    }    
}

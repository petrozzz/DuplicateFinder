#include "pathdiscobject.h"
#include "filediscobject.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <QDebug>

using namespace std;

PathDiscObject::PathDiscObject(){
}

PathDiscObject::PathDiscObject(std::string root, std::string name):DiscObject(root, name){
    //qDebug() << (getRoot() + "/" + getName()).data();
    calcDiscObject();
}

DiscObjectType PathDiscObject::get_type(){
    return DiscObjectType::PathObject;
}

void PathDiscObject::calcDiscObject(){
    DIR *path = NULL;
    qDebug() << (this->getRoot() + this->getName()).data();
    path = opendir((this->getRoot() + this->getName()).data());
    if(path == 0x0)
        return;
    //qDebug() << (getRoot() + "/" + getName()).data();
    struct dirent *dir_entry;
    struct stat file_info;
    //int iter = 0;
    while((dir_entry = readdir(path))!= NULL){
        //printf(" %s", dir_entry->d_name);       
        qDebug() << (this->getRoot() + this->getName() + "/"+ (string)(dir_entry->d_name)).data();
        stat((this->getRoot() + this->getName() + "/"+ (string)(dir_entry->d_name)).data() , &file_info);
        switch(file_info.st_mode & S_IFMT){
        case S_IFBLK:
            //printf("\t - block device\n");
            break;
        case S_IFCHR:
            //printf("\t - carecter device\n");
            break;
        case S_IFDIR:
            //printf("\t - directory\n");
            if((strcmp(dir_entry->d_name, "..")!=0) && (strcmp(dir_entry->d_name, "."))!=0){
                discobjects.push_back((DiscObject)(PathDiscObject(this->getRoot()+this->getName()+"/",dir_entry->d_name)));
                (discobjects.back()).do_type = "Dir";
            }
            break;
        case S_IFSOCK:
            //printf("\t - socket\n");
            break;
        case S_IFREG:
            discobjects.push_back((DiscObject)(FileDiscObject(this->getName(),dir_entry->d_name)));
            (discobjects.back()).do_type = "File";
            //printf("\t - regular file\n");
            break;
        default:
            printf("\t - unknown\n");
        }
    }
    closedir(path);

}

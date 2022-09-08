#pragma once

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <QDir>
using namespace std;

void useqt(){
    cout << "fileclassifier start" << endl;
    QString dirPath("..");
    QStringList fileNameList;
    fileNameList << QDir(dirPath).entryList(QDir::Files);
    cout << "files:\n";
    foreach (QString fileName, fileNameList)    {
        QFileInfo finfo(fileName);
        //cout << finfo.fileName().toStdString() << " " << finfo. << endl;

    }
    QDir(dirPath).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList subDirNameList;
    subDirNameList << QDir(dirPath).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    cout << "dir:\n";
    foreach (QString dirName, subDirNameList)    {
        cout << dirName.toStdString() << endl;
    }
    cout << "fileclassifier end" << endl;
}

void usestd(){
    DIR *path = NULL;
    path = opendir("..");
    struct dirent *dir_entry;
    struct stat file_info;
    char buff[256];
    strcpy(buff, "../");
    while((dir_entry = readdir(path))!= NULL){
        printf(" %s", dir_entry->d_name);
        strcpy(buff, "../");
        strcat(buff, dir_entry->d_name);
        stat(buff, &file_info);
        switch(file_info.st_mode & S_IFMT){
        case S_IFBLK:
            printf("\t - block device\n");
            break;
        case S_IFCHR:
            printf("\t - carecter device\n");
            break;
        case S_IFDIR:
            printf("\t - directory\n");
            break;
        case S_IFSOCK:
            printf("\t - socket\n");
            break;
        case S_IFREG:
            printf("\t - regular file\n");
            break;
        default:
            printf("\t - unknown\n");
        }
    }
    closedir(path);
}

void main_fileclassifier(){
    usestd();
}

#include "dbdiscobject.h"
#include <string.h>

using std::string;

DBDiscObject::DBDiscObject(PathDiscObject path){
    this->path = path;
    discObjects.clear();
}

void DBDiscObject::getDiscObject(PathDiscObject path){
    DIR *dir_path = NULL;
    char buff[1024];
    strcpy(buff, path.getRoot().data());
    strcat(buff, "/");
    strcat(buff, path.getName().data());

    dir_path = opendir(buff);
    struct dirent *dir_entry;
    struct stat file_info;

    while((dir_entry = readdir(dir_path))!= NULL){
        //printf(" %s", dir_entry->d_name);
        //strcpy(buff, "../");
        string str = dir_entry->d_name;
        strcat(buff, str.data());
        stat(buff, &file_info);
        switch(file_info.st_mode & S_IFMT){
        case S_IFBLK:
            //printf("\t - block device\n");
            break;
        case S_IFCHR:
            //printf("\t - carecter device\n");
            break;
        case S_IFDIR:
            //printf("\t - directory\n");

            break;
        case S_IFSOCK:
            //printf("\t - socket\n");
            break;
        case S_IFREG:
            //printf("\t - file\n");
            //discObjects.push_back((DiscObject)(FileDiscObject(path.getRoot(), str)));
            break;
        default:
            printf("\t - unknown\n");
        }
    }
    closedir(dir_path);
}

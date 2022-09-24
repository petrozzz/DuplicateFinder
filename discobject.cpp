#include "discobject.h"
//#include <openssl/md5.h>

using std::string;

DiscObject::DiscObject(){
}

DiscObject::DiscObject(string root, string name){
    this->root = root;
    this->name = name;
    QFileInfo fileInfo(QDir(root.data()), name.data());
    size = fileInfo.size();
    create_time = fileInfo.created().toString("dd.MM.yyyy hh:mm:ss").toStdString();
    modified_time = fileInfo.lastModified().toString("dd.MM.yyyy hh:mm:ss").toStdString();
    group = "0";
    if(fileInfo.isFile()){
        group = getHash();
    }
}

std::string DiscObject::getHash(){
    /*if(size > 0){

        QFile fl((root + "/" + name).data());
        fl.open(QFile::ReadOnly);
        QString str = fl.readAll().toStdString().data();
        unsigned char result[MD5_DIGEST_LENGTH];
        MD5((unsigned char*)str.data(), str.length(), result);
        QString res;
        for(int k = 0; k < MD5_DIGEST_LENGTH; ++k){
            res.push_back(QString("%1").arg(result[k],2,16,QChar('0')));
            if(k == 3 || k == 5 || k == 7  || k == 9)
                res.push_back('-');
        }
        fl.close();
        return res.toStdString();
    } else
    */
        return "0";
}


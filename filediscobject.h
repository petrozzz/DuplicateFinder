#ifndef FILEDISCOBJECT_H
#define FILEDISCOBJECT_H
#include "discobject.h"
#include <fstream>

class FileDiscObject : public DiscObject
{

public:
    FileDiscObject(): DiscObject(){}
    FileDiscObject(string root, string name) : DiscObject(root, name){}
    DiscObjectType get_type() const{
        return DiscObjectType::FileObject;
    }

    bool operator==(FileDiscObject const &fileDiscObject) const{
        if (this == &fileDiscObject)
            return true;
        if((root == fileDiscObject.getRoot()) && (name == fileDiscObject.getName()))
            return true;
        if(fileDiscObject.getSize() != size)
            return false;       
        FILE *fl1;
        FILE *fl2;
        char ch1, ch2;
        bool is_equal = true;
        if((fl1 = fopen((root + "/" + name).data(), "rb")) &&
           (fl2 = fopen((fileDiscObject.getRoot() + "/" + fileDiscObject.getName()).data(), "rb"))){
            while(feof(fl1)){
                fread(&ch1, sizeof(ch1), 1, fl1);
                fread(&ch2, sizeof(ch2), 1, fl2);
                if((ch1 | ch2) != 0){
                    is_equal = false;
                    break;
                }
            }
            fclose(fl1);
            fclose(fl2);
        }       
        return is_equal;
    }
};
#endif // FILEDISCOBJECT_H

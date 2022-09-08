#ifndef FILEDISCOBJECT_H
#define FILEDISCOBJECT_H
#include "discobject.h"

class FileDiscObject : public DiscObject
{
    string root;
    string name;
    long size;
    string create_time;

public:
    FileDiscObject();
    FileDiscObject(string root, string name);
    long getSize();
    virtual DiscObjectType get_type() override;

private:


};

#endif // FILEDISCOBJECT_H

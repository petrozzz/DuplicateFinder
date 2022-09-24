#ifndef PATHDISCOBJECT_H
#define PATHDISCOBJECT_H
#include "discobject.h"
#include "filediscobject.h"
#include <string>
#include <list>

using std::string;

class PathDiscObject: public DiscObject
{
public:
    std::list<DiscObject> discobjects;
public:
    PathDiscObject();
    PathDiscObject(string root, string name);
    DiscObjectType get_type();

    ~PathDiscObject(){
        discobjects.clear();
    }

public:
    std::list<DiscObject> getDiscObjects() const{
        return discobjects;
    }

    void calcDiscObject();

    void PathDiscObject::getAllFiles(std::list<FileDiscObject> &all_files);
};

#endif // PATHDISCOBJECT_H

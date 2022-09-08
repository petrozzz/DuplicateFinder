#ifndef PATHDISCOBJECT_H
#define PATHDISCOBJECT_H
#include "discobject.h"
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
    virtual DiscObjectType get_type() override;

    ~PathDiscObject(){
        discobjects.clear();
    };

public:
    std::list<DiscObject> getDiscObjects() const{
        return discobjects;
    }

    void calcDiscObject();
};

#endif // PATHDISCOBJECT_H

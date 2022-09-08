#ifndef ABSTARCTDISCOBJECT_H
#define ABSTARCTDISCOBJECT_H

#include <string>

using std::string;

enum DiscObjectType{FileObject, PathObject};

class DiscObject
{
protected:
    string root; // PathDiscObject* root; - так можно???
    string name;
    string create_time;

public:

    string do_type;

    DiscObject();
    DiscObject(string root, string name);
    string getRoot();
    string getName();
    string getCreateTime();
    virtual DiscObjectType get_type(){};

protected:
    void init();

};

#endif // ABSTARCTDISCOBJECT_H

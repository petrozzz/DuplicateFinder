#ifndef ABSTARCTDISCOBJECT_H
#define ABSTARCTDISCOBJECT_H

#include <string>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>


using std::string;

enum DiscObjectType{FileObject, PathObject};

class DiscObject
{
protected:
    string root; // PathDiscObject* root; - так можно???
    string name;
    string create_time;
    string modified_time;
    long long size;
    string group;

public:

    string do_type;

    DiscObject();
    DiscObject(string root, string name);
    string getRoot() const{
        return root;
    }
    string getName() const{
        return name;
    }
    long long getSize() const{
        return size;
    }
    string getGroup() const{
        return group;
    }
    string getCreateTime() const{
        return create_time;
    }
    string getModifiedTime() const{
        return modified_time;
    }
    DiscObjectType get_type() {
        //do virtual
    }

protected:   
    string getHash();

};

#endif // ABSTARCTDISCOBJECT_H

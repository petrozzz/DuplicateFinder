#ifndef DBDISCOBJECT_H
#define DBDISCOBJECT_H


#include "discobject.h"
#include "filediscobject.h"
#include "pathdiscobject.h"

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

class DBDiscObject
{
    PathDiscObject path;
    vector<DiscObject> discObjects;

public:
    DBDiscObject(PathDiscObject path);

private:
    void getDiscObject(PathDiscObject path);
};

#endif // DBDISCOBJECT_H

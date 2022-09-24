#include "dbdiscobject.h"
#include <string.h>

using std::string;

DBDiscObject::DBDiscObject(PathDiscObject path){
    this->path = path;
    discObjects.clear();
}

#include "discobject.h"

using std::string;

DiscObject::DiscObject(){
}

DiscObject::DiscObject(string root, string name){
    this->root = root;
    this->name = name;
}

std::string DiscObject::getName(){
    return name;
}

std::string DiscObject::getRoot(){
    return root;
}

std::string DiscObject::getCreateTime(){
    return create_time;
}

void DiscObject::init(){

}

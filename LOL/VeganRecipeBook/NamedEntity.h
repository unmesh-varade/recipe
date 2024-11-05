#ifndef NAMEDENTITY_H
#define NAMEDENTITY_H

#include <string>
using namespace std;

class NamedEntity {
public:
    string name;

    NamedEntity() : name("") {}
    NamedEntity(string n) : name(n) {}
};

#endif

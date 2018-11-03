#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "room.h"

using namespace std;

class item{
  public:
    string name;
    string status;
    string description;
    string writing;
    string turn_on;
    string action_on;

    string getName(item itemx);
    void printName(item itemx);
    //void printStatus(item itemx);
    void printDescription(item itemx);
    void readItem(item itemx);
    //item turn_on_func(item itemx, roomy);
};

#endif

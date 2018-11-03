#ifndef ITEM_H
#define ITEM_H
#include "room.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>


using namespace std;

class item{
  public:
    string name;
    string status;
    string description;
    string writing;
    string turn_on;
    string action_on;
    string curr_room_name;

    string getName(item itemx);
    void printName(item itemx);
    void readItem(item itemx);
    void turn_on_func(item itemx);
    //void printStatus(item itemx);
    //item turn_on_func(item itemx, roomy);
};

#endif

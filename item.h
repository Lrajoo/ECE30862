#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <string>
#include "room.h"

class item{
  string name;
  string status;
  string description;
  string writing;
  string turn_on;
  string on_action;

  string getName(item itemx);
  void printName(item itemx);
  //void printStatus(item itemx);
  void printDescription(item itemx);
  void readItem(item itemx);
  void turn_on(room* roomy, item itemx);
}

#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "trigger.h"
#include "room.h"

using namespace std;

class container{
 public:
  string name;
  string status;
  string description;
  vector <string> accept;
  string item;
  trigger triggers;
  bool flag;

  string getName(container contains);
  void printName(container contains);
  void printItems(container contains);
  bool hasItems(container contains);
  void printAccept(container contains);
  bool hasAccept(container contains);
};

#endif

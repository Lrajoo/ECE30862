#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "trigger.h"

using namespace std;

class container{
 public:
  string name;
  string status;
  string description;
  vector <string> accept;
  vector <string> item;
  trigger triggers;

  string getName(container contains);
  void printName(container contains);
  void printItems(container contains);
  bool hasItems(container contains);
  void printAccept(container contains);
  bool hasAccept(container contains);
};

#endif

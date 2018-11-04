#ifndef CREATURE_H
#define CREATURE_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "trigger.h"

using namespace std;

class creature{
 public:
  string name;
  string status;
  string description;
  vector <string> vulnerability;
  string attack;
  trigger triggers;
  string owner;
  vector <string> action;

  string getName(creature kreacher);
  void printName(creature kreacher);
  void printVulnerability(creature kreacher);
  bool checkVulnerability(creature kreacher, string item);
  void printAttack(creature kreacher);
};

#endif

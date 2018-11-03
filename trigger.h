#ifndef TRIGGER_H
#define TRIGGER_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class condition{
 public:
  string object;
  string owner;
  string has;
  string status;
  bool validated;

  bool validate(condition conditioner, string object, string owner, string has, string status);
};

class trigger{
 public:
  condition conditioner;
  string print;
  vector<string> action;
  string command;
  string type;
  bool valid;

  void printTrigger(trigger triggered, string command);
  bool setValid(trigger triggered);
};

#endif

#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <string>
#include <vector>
#include "trigger.h"

using namespace std;

class room{
public:
  //room();
  //virtual ~room();
  string description;
  string north;
  string south;
  string east;
  string west;
  string type;
  string name;
  vector <string> creature;
  trigger triggered;

  //item vector
  vector<string> item_vector;
  //container vector
  vector<string> container_vector;
  
  void getBorders(room roomy);
  string getName(room roomy);
  string getType(room roomy);
  void getDescription(room roomy);
  string moveRoom(room roomy, string input);
  void printName(room roomy);
  bool getItem(room roomy, string itemx);
};

#endif

#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <string>

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


  void getBorders(room roomy);
  void getName(room roomy);
  void getType(room roomy);
  void getDescription(room roomy);
};

#endif
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
  string getName(room roomy);
  string getType(room roomy);
  void getDescription(room roomy);
  string moveRoom(room roomy, string input);
  void printName(room roomy);
};

#endif

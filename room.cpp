#include "room.h"
#include "stdio.h"
#include <iostream>

//using namespace std;

void room::getBorders(room roomy){
  if(!roomy.north.compare(" ")){
    cout << "North: " << roomy.north << endl;
  }
  if(!roomy.south.compare(" ")){
    cout << "South: " << roomy.south << endl;
  }
  if(!roomy.east.compare(" ")){
    cout << "East: " << roomy.east << endl;
  }
  if(!roomy.west.compare(" ")){
    cout << "West: " << roomy.west << endl;
  }
}

void room::getName(room roomy){
  cout << roomy.name << endl;
}

void room::getType(room roomy){
  cout << roomy.type << endl;
}

void room::getDescription(room roomy){
  cout << roomy.description << endl;
}

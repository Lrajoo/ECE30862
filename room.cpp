#include "room.h"
#include "stdio.h"
#include <iostream>

//using namespace std;
string room::moveRoom(room roomy, string input){
  if(input == "n"){
    if(roomy.north != ""){
      return roomy.north; 
    }
    else{
      cout << "No where to go" << endl;
      string name = roomy.getName(roomy);
      return name;
    }
  }
  if(input == "s"){
    if(roomy.south != ""){
      return roomy.south; 
    }
    else{
      cout << "No where to go" << endl;
      string name = roomy.getName(roomy);
      return name;
    }
  }
  if(input == "e"){
    if(roomy.east != ""){
      return roomy.east; 
    }
    else{
      cout << "No where to go" << endl;
      string name = roomy.getName(roomy);
      return name;
    }
  }
  if(input == "w"){
    if(roomy.west != ""){
      return roomy.west; 
    }
    else{
      cout << "No where to go" << endl;
      string name = roomy.getName(roomy);
      return name;
    }
  }
  else{
    return "error";
  };
}

void room::getBorders(room roomy){
  if(roomy.north != ""){
    cout << "North: " << roomy.north << endl;
  }
  if(roomy.south != ""){
    cout << "South: " << roomy.south << endl;
  }
  if(roomy.east != ""){
    cout << "East: " << roomy.east << endl;
  }
  if(roomy.west != ""){ 
    cout << "West: " << roomy.west << endl;
  }
}
string room::getName(room roomy){
  return roomy.name;
}

void room::printName(room roomy){
  cout << roomy.name << endl;
}

string room::getType(room roomy){
  return roomy.type;
}

void room::getDescription(room roomy){
  cout << roomy.description << endl;
}



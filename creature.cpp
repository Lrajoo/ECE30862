#include "creature.h"

string creature::getName(creature kreacher){
  return kreacher.name;
}

void creature::printName(creature kreacher){
  cout << kreacher.name;
}

void creature::printVulnerability(creature kreacher){
  int size = kreacher.vulnerability.size();
  int i;
  cout << kreacher.vulnerability[0];
  if(size > 1){
    for(i = 1; i < size; i++){
      cout << ", " << kreacher.vulnerability[i];
    }
  }
}

bool creature::checkVulnerability(creature kreacher, string item){
  int size = kreacher.vulnerability.size();
  int i;
  if(item == kreacher.vulnerability[0]){
    return 1;
  }
  else if(size > 1){
    for(i = 1; i < size; i++){
      if(item == kreacher.vulnerability[i]){
	return 1;
      }
    }
  }
  return 0;
}

void creature::printAttack(creature kreacher){
  cout << kreacher.attack << endl;
}

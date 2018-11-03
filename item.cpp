#include "item.h"

string item::getName(item itemx){
  return itemx.name;
}

void item::printName(item itemx){
  cout << itemx.name << end;
}
void item::printDescription(item itemx){
  cout << itemx.description << end;
}

void item::readItem(item itemx){
  cout << itemx.writing << end;
}

item item::turn_on(room* roomy, item itemx){
  cout << itemx.turn_on << endl;
  int size = itemx.on_action.size();
  for(int i = 0; i < size; i++){
    if(i+3 < size){
      if(itemx.on_action[i] == "d"){
	if(itemx.on_action[i+1] == "r"){
	  if(itemx.on_action[i+2] == "o"){
	    if(itemx.on_action[i+3] == "p"){
	      roomy->add(&roomy, itemx);
	    }
	  }
	}
      }
    }
  }
  return itemx;
}

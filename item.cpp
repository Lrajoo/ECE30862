#include "item.h"
#include "room.h"
#include "stdio.h"
#include <string.h>
#include <iostream>

using namespace std;

string item::getName(item itemx){
  return itemx.name;
}

void item::printName(item itemx){
  cout << itemx.name << endl;
}

void item::readItem(item itemx){
  if(itemx.writing == ""){
    cout << "Nothing written" << endl;
  }
  else{
     cout << itemx.writing << endl;
  }
}

void item::turn_on_func(item itemx){
  cout << "You activate the " << itemx.name << endl;
  cout << itemx.turn_on << endl;
}


//item item::turn_on_func(item itemx,room roomy){
//   cout << itemx.turn_on << endl;

//   int size = itemx.action_on.size();
//   for(int i = 0; i < 4; i++){
//     if(itemx.action_on[i] == 'd'){
// 	  if(itemx.action_on[i+1] == 'r'){
// 	  if(itemx.action_on[i+2] == 'o'){
// 	  if(itemx.action_on[i+3] == 'p'){
// 	      //roomy->add(&roomy, itemx);
// 	    }
// 	  }
// 	}
//       }
//     }
  
//   return itemx;
// }
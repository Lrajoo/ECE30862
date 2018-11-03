#include "trigger.h"

bool condition::validate(condition conditioner, string object, string owner, string has, string status){
  int chk = 0;
  int chk2 = 0;
  int chk3 = 0;
  int chk4 = 0;
  if(conditioner.object == " "){
    chk = 1;
  }
  else{
    if(conditioner.object == object){
      chk = 1;
    }
  }
  if(conditioner.owner == " "){
    chk2 = 1;
  }
  else{
    if(conditioner.owner == owner){
      chk2 = 1;
    }
  }
  if(conditioner.has == " "){
    chk3 = 1;
  }
  else{
    if(conditioner.has == has){
      chk3 = 1;
    }
  }
  if(conditioner.status == " "){
    chk4 = 1;
  }
  else{
    if(conditioner.status == status){
      chk4 = 1;
    }
  }

  if(chk == 1 && chk2 == 1 && chk3 == 1 && chk4 == 1){
    return 1;
  }
  return 0;
  
}

void trigger::printTrigger(trigger triggered, string command){
  if(triggered.command == command){
    if(triggered.conditioner.validated){
      if(triggered.print != " "){
	cout << triggered.print << endl;
      }
    }
  }
}

bool trigger::setValid(trigger triggered){
  if(triggered.type == "single"){
    return 0;
  }
  return 1;
}


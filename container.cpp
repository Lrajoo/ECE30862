#include "container.h"

string container::getName(container contains){
  return contains.name;
}

void container::printName(container contains){
  cout << contains.name;
}

void container::printItems(container contains){
  int i;
  int size = contains.item.size();
  cout << contains.item[0];
  if(size > 1){
    for(i = 1; i < size; i++){
      cout << ", " << contains.item[i];
    }
  }
}

bool container::hasItems(container contains){
  int size = contains.item.size();
  if(size == 0){
    return 0;
  }
  else{
    return 1;
  }
}

bool container::hasAccept(container  contains){
  int size =  contains.accept.size();
  if(size == 0){
    return 0;
  }
  else{
    return 1;
  }
}

void container::printAccept(container contains){
  int i;
  int size = contains.accept.size();
  cout << contains.accept[0];
  if(size > 1){
    for(i = 1; i < size; i++){
      cout << ", " << contains.item[i];
    }
  }
}

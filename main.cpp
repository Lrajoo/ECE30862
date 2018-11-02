//  Copyright © 2018 Lingess Rajoo. All rights reserved.
//
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

int main(int argc, char * argv[])
{
    cout << "Parsing now" << endl;
    
    xml_document<> doc;
    xml_node<> * root_node;
    ifstream file("roomsample.xml");
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content(buffer.str());
    doc.parse<0>(&content[0]);
    
    root_node = doc.first_node("map");
    xml_node<> * room_node = root_node->first_node("room");
    xml_node<> * name_node = room_node->first_node("name");
    cout << name_node->value() << endl; 

    return 0;
}

//  Copyright © 2018 Lingess Rajoo. All rights reserved.
//
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "room.h"

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
//#include "rapidxml-1.13/rapidxml_iterators.hpp"

using namespace rapidxml;
using namespace std;

int main(int argc, char * argv[])
{   
    //xml intialization for parsing
    xml_document<> doc;
    //input file to be parsed
    ifstream file("roomsample.xml");
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content(buffer.str());
    doc.parse<0>(&content[0]);
    //vectors for room, item, container and creature 
    vector<room> room_vector;
    vector<xml_node<> * > item_vector;
    vector<xml_node<> * > container_vector;
    vector<xml_node<> * > creature_vector; 
    //root node
    xml_node<> * root_node = doc.first_node("map");
    //scanning through file and identifying rooms, items, containers and creatures
    for(xml_node<> * curr_node = root_node->first_node(); curr_node; curr_node = curr_node->next_sibling()){
        room roomy;
        if(string(curr_node->name()) == "room"){
            roomy.name = curr_node->first_node("name")->value();
            roomy.description = curr_node->first_node("description")->value();
            if(curr_node->first_node("type")){
                roomy.type = curr_node->first_node("type")->value();
            }
            for(xml_node<> * border = curr_node->first_node("border"); border; border = border->next_sibling()){
                if(string(border->value()) != "exit"){
                    if(string(border->first_node("direction")->value()) == "north"){
                        roomy.north = border->first_node("name")->value();
                    }
                    if(string(border->first_node("direction")->value()) == "south"){
                        roomy.south = border->first_node("name")->value();
                    }
                    if(string(border->first_node("direction")->value()) == "east"){
                        roomy.east = border->first_node("name")->value();
                    }
                    if(string(border->first_node("direction")->value()) == "west"){
                        roomy.west = border->first_node("name")->value();
                    }
                }
            }
            room_vector.push_back(roomy);
        }
    }

    int size = room_vector.size();
    int i = 0;
    // while( i < size){
    //     room curr = room_vector[i];
    //     curr.getName(curr);
    //     curr.getDescription(curr);
    //     curr.getType(curr);
    //     curr.getBorders(curr);
    //     i++;
    // }
    string input_command;
    string curr_room_str;
    string dummy;
    room curr_room = room_vector[0];
    room prev_room = room_vector[0];
    prev_room.getName(room_vector[0]);
    room_vector[0].getDescription(room_vector[0]);

    while(1){
        prev_room = curr_room;
        cout << ">";
        cin >> input_command;
        if(string(input_command) == "n" || "s" || "e" || "w"){
             curr_room_str = prev_room.moveRoom(prev_room, input_command);
             if(prev_room.getName(prev_room) != curr_room_str){
                for(i=0; i < size; i++){
                    if(string(room_vector[i].getName(room_vector[i])) == curr_room_str){
                        curr_room = room_vector[i];
                        curr_room.printName(curr_room);
                        curr_room.getDescription(curr_room);
                        break;
                    }
                }
             }
          
        }
    }

    return 0;
}

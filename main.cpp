//  Copyright © 2018 Lingess Rajoo. All rights reserved.
//
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "item.h"
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
    ifstream file("itemsample.xml");
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content(buffer.str());
    doc.parse<0>(&content[0]);
    //vectors for room, item, container and creature 
    vector<room> room_vector;
    vector<item> item_vector;
    vector<string> inventory_vector;
    //vector<xml_node<> * > container_vector;
    //vector<xml_node<> * > creature_vector; 
    //root node
    xml_node<> * root_node = doc.first_node("map");
    //scanning through file and identifying rooms
    //curr = room

    for(xml_node<> * curr_node = root_node->first_node(); curr_node; curr_node = curr_node->next_sibling()){
        room roomy;
        string item_room_location;
        if(string(curr_node->name()) == "room"){
            roomy.name = curr_node->first_node("name")->value();
            roomy.description = curr_node->first_node("description")->value();
            if(curr_node->first_node("type")){
                roomy.type = curr_node->first_node("type")->value();
            }
            for(xml_node<> * item_parse = curr_node->first_node("item"); item_parse; item_parse = item_parse->next_sibling("item")){
                    item_room_location = item_parse->value();
                    roomy.item_vector.push_back(item_room_location);
                    //cout << item_room_location << endl;
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
    //scanning through file and identifying items
    for(xml_node<> * item_node = root_node->first_node("item"); item_node; item_node = item_node->next_sibling()){
        item itemy;
        itemy.name = item_node->first_node("name")->value();
        //itemy.description = item_node->first_node("description")->value();
        if(item_node->first_node("writing")){
            itemy.writing = item_node->first_node("writing")->value();
        }
        if(item_node->first_node("turnon")){
            itemy.turn_on = item_node->first_node("turnon")->first_node("print")->value();
            itemy.action_on = item_node->first_node("turnon")->first_node("action")->value();
        }
    
        item_vector.push_back(itemy);
    }
    int size_item = item_vector.size();
    int j = 0;
    //item curr_item = item_vector[0];

    int size_room = room_vector.size();
    int i = 0;
    string check_exit;
    string input_command;
    string curr_room_str;
    room curr_room = room_vector[0];
    room prev_room = room_vector[0];
    prev_room.getName(room_vector[0]);
    room_vector[0].getDescription(room_vector[0]);
    //curr_room.getItem(curr_room);

    while(1){
        prev_room = curr_room;
        check_exit = prev_room.getType(prev_room);
        cout << ">";
        //input command
        std::getline(std::cin,input_command);
        //spilt string
        string delimiter = " ";
        string command = input_command.substr(0, input_command.find(delimiter));
        //open exit
        if(string(input_command) == "open exit" && check_exit != ""){
            cout << "Game Over" << endl;
            return 0;
        }else if(string(input_command) == "i"){
            int l = 0;
            int size_inventory = inventory_vector.size();
            if(size_inventory == 0){
                cout << "Inventory empty" << endl;
            }else{
                cout << "Inventory: ";
                for(l=0; l < size_inventory; l++){
                    if(l == 0){
                        cout << inventory_vector[l];
                    }
                    else{
                        cout << ", " << inventory_vector[l];
                    }
                    
                }
                cout << endl;
            }
        }else if(command == "turn"){
            std::size_t pos = input_command.find("on");
            std::string action_item = input_command.substr(pos);
            int length = action_item.size();
            string item_name = action_item.substr(3);
            //check if exists in inventory
            int k;
            int size_i = inventory_vector.size();
            int item_in_inventory = 0;
            int vector_num;
            for(k=0; k<size_i; k++){
                if(inventory_vector[k] == item_name){
                    item_in_inventory = 1;
                    vector_num = k;
                }
            }
            if(item_in_inventory == 1){
                int size_item_vector = item_vector.size();
                int m;
                for(m=0; m<size_item_vector; m++){
                    if(item_vector[m].name == item_name){
                        item_vector[m].turn_on_func(item_vector[m]);
                    }
                }
            }
        }else if(command == "put"){

            string item_name = input_command.substr(4);
            
        }else if(command == "drop"){  
            string item_name = input_command.substr(5);
            //check if item is in inventory
            int k;
            int size_i = inventory_vector.size();
            int item_exists = 0;
            int vector_num;
            for(k=0; k<size_i; k++){
                if(inventory_vector[k] == item_name){
                    item_exists = 1;
                    vector_num = k;
                }
            }
            //add back to the room
            curr_room.item_vector.push_back(inventory_vector[vector_num]);
            //remove item from vector
            inventory_vector.erase(inventory_vector.begin() + vector_num - 1) ;
        }else if(command == "take"){    //take item and adds to inventory
            string item_name = input_command.substr(5);
            //check if item exists in inventory
            int k;
            int size_i = inventory_vector.size();
            int item_exists = 0;
            for(k=0; k<size_i; k++){
                if(inventory_vector[k] == item_name){
                    cout << "Item exists in inventory" << endl;
                    item_exists = 1;
                }
            }
            if(curr_room.getItem(curr_room,item_name) && item_exists == 0){
                //add to inventory
                inventory_vector.push_back(item_name);
                cout<< "Item " << item_name << " added to inventory" << endl;
            }
            //item that doesn't exist
            if(!curr_room.getItem(curr_room,item_name) && item_exists == 0) {
                cout << "Command not recognized" << endl;
            }
        }else if(string(input_command) == "n" || "s" || "e" || "w"){
             curr_room_str = prev_room.moveRoom(prev_room, input_command);
             if(string(curr_room_str) == "error"){
                cout << "Command not recognized" << endl;
             }
             else if(prev_room.getName(prev_room) != curr_room_str){
                for(i=0; i < size_room; i++){
                    if(string(room_vector[i].getName(room_vector[i])) == curr_room_str){
                        curr_room = room_vector[i];
                        curr_room.printName(curr_room);
                        curr_room.getDescription(curr_room);
                        //curr_room.getItem(curr_room);
                        break;
                    }
                }
             }
        }        
    }

    return 0;
}


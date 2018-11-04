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
#include "container.h"
#include "creature.h"


#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
//#include "rapidxml-1.13/rapidxml_iterators.hpp"

using namespace rapidxml;
using namespace std;

int main(int argc, char * argv[]) {
    //xml intialization for parsing
    xml_document<> doc;
    //input file to be parsed
    ifstream file("C:/Users/Xaxx/Desktop/ECE30862/ECE30862-master/creaturesample.xml");
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    string content(buffer.str());
    doc.parse<0>(&content[0]);
    //vectors for room, item, container and creature 
    vector<room> room_vector;
    vector<item> item_vector;
    vector<string> inventory_vector;
    vector<container> container_vector;
    vector<creature> creature_vector;
    vector<trigger> trigger_vector;
    //root node
    xml_node<> * root_node = doc.first_node("map");
    //scanning through file and identifying rooms
    //curr = room
    for (xml_node<> * curr_node = root_node->first_node("room"); curr_node; curr_node = curr_node->next_sibling("room")) {
        room roomy;
        string item_room_location;
        string container_room_location;
        if (string(curr_node->name()) == "room") {
            roomy.name = curr_node->first_node("name")->value();
            roomy.description = curr_node->first_node("description")->value();
            if (curr_node->first_node("type")) {
                roomy.type = curr_node->first_node("type")->value();
            }
            for (xml_node<> * item_parse = curr_node->first_node("item"); item_parse; item_parse = item_parse->next_sibling("item")) {
                item_room_location = item_parse->value();
                roomy.item_vector.push_back(item_room_location);
                //cout << item_room_location << endl;
            }
            for (xml_node<> * container_parse = curr_node->first_node("container"); container_parse; container_parse = container_parse->next_sibling("container")) {
                container_room_location = container_parse->value();
                roomy.container_vector.push_back(container_room_location);
            }
            if (curr_node->first_node("creature")) {
                roomy.creature.push_back(curr_node->first_node("creature")->value());
            }
            for (xml_node<> * border = curr_node->first_node("border"); border; border = border->next_sibling("border")) {
                if (string(border->value()) != "exit") {
                    if (string(border->first_node("direction")->value()) == "north") {
                        roomy.north = border->first_node("name")->value();
                    }
                    if (string(border->first_node("direction")->value()) == "south") {
                        roomy.south = border->first_node("name")->value();
                    }
                    if (string(border->first_node("direction")->value()) == "east") {
                        roomy.east = border->first_node("name")->value();
                    }
                    if (string(border->first_node("direction")->value()) == "west") {
                        roomy.west = border->first_node("name")->value();
                    }
                }
            }
            for (xml_node<> * trigger_node = curr_node->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {    
                trigger triggery;
                if (trigger_node->first_node("type")) {
                    triggery.type = trigger_node->first_node("type")->value();
                }
                if (trigger_node->first_node("command")) {
                    triggery.command = trigger_node->first_node("command")->value();
                }
                for (xml_node<> * action_node = trigger_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
                     triggery.action.push_back(action_node->value());
                }
                if (trigger_node->first_node("print")) {
                    triggery.print = trigger_node->first_node("print")->value();
                }
                if (trigger_node->first_node("condition")) {
                    if (trigger_node->first_node("condition")->first_node("object")) {
                        triggery.conditioner.object = trigger_node->first_node("condition")->first_node("object")->value();
                    }
                    if (trigger_node->first_node("condition")->first_node("owner")) {
                        triggery.conditioner.owner = trigger_node->first_node("condition")->first_node("owner")->value();
                    }
                    if (trigger_node->first_node("condition")->first_node("has")) {
                        triggery.conditioner.has = trigger_node->first_node("condition")->first_node("has")->value();
                    }
                    if (trigger_node->first_node("condition")->first_node("status")) {
                        triggery.conditioner.status = trigger_node->first_node("condition")->first_node("status")->value();
                    }
                }
                roomy.triggered = triggery;
                //trigger_vector.push_back(triggery);
            }       
            room_vector.push_back(roomy);
        } 
    }
    //scanning through file and identifying items
    for (xml_node<> * item_node = root_node->first_node("item"); item_node; item_node = item_node->next_sibling("item")) {
        item itemy;

        itemy.name = item_node->first_node("name")->value();
        //itemy.description = item_node->first_node("description")->value();
        if (item_node->first_node("writing")) {
            itemy.writing = item_node->first_node("writing")->value();
        }
        if (item_node->first_node("turnon")) {
            itemy.turn_on = item_node->first_node("turnon")->first_node("print")->value();
            itemy.action_on = item_node->first_node("turnon")->first_node("action")->value();
        }
        if (item_node->first_node("status")) {
            itemy.status = item_node->first_node("status")->value();
        }

        item_vector.push_back(itemy);
    }
    //scanning through file and identifying containers
    for (xml_node<> * container_node = root_node->first_node("container"); container_node; container_node = container_node->next_sibling("container")) {
        container containery;
        containery.name = container_node->first_node("name")->value();

        if (container_node->first_node("item")) {
            containery.item = container_node->first_node("item")->value();
        }
        if (container_node->first_node("accept")) {
            containery.accept.push_back(container_node->first_node("accept")->value());
        }
        for (xml_node<> * trigger_node = container_node->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {
            trigger triggery;
            if (trigger_node->first_node("type")) {
                triggery.type = trigger_node->first_node("type")->value();
            }
            if (trigger_node->first_node("command")) {
                triggery.command = trigger_node->first_node("command")->value();
            }
            for (xml_node<> * action_node = trigger_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
                triggery.action.push_back(action_node->value());
            }
            if (trigger_node->first_node("print")) {
                triggery.print = trigger_node->first_node("print")->value();
            }
            if (trigger_node->first_node("condition")) {
                if (trigger_node->first_node("condition")->first_node("object")) {
                    triggery.conditioner.object = trigger_node->first_node("condition")->first_node("object")->value();
               }
                if (trigger_node->first_node("condition")->first_node("owner")) {
                    triggery.conditioner.owner = trigger_node->first_node("condition")->first_node("owner")->value();
                }
                if (trigger_node->first_node("condition")->first_node("has")) {
                    triggery.conditioner.has = trigger_node->first_node("condition")->first_node("has")->value();
                }
                if (trigger_node->first_node("condition")->first_node("status")) {
                triggery.conditioner.status = trigger_node->first_node("condition")->first_node("status")->value();
                }
            }   
            containery.triggers = triggery;
        }   
        container_vector.push_back(containery);
    }
    //scanning through file and identifying creatures
    for (xml_node<> * creature_node = root_node->first_node("creature"); creature_node; creature_node = creature_node->next_sibling("creature")) {
        creature creaturey;
        creaturey.name = creature_node->first_node("name")->value();
        if (creature_node->first_node("vulnerability")) {
            for (xml_node<> * vulnerabilty_node = creature_node->first_node("vulnerability"); vulnerabilty_node; vulnerabilty_node = vulnerabilty_node->next_sibling("vulnerability")) {
                creaturey.vulnerability.push_back(vulnerabilty_node->value());
            }
        }
        if (creature_node->first_node("attack")) {
            for (xml_node<> * action_node = creature_node->first_node("attack")->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
                creaturey.action.push_back(action_node->value());
            }
            if (creature_node->first_node("attack")->first_node("print")) {
                creaturey.attack = creature_node->first_node("attack")->first_node("print")->value();
            }
        }
        for (xml_node<> * trigger_node = creature_node->first_node("trigger"); trigger_node; trigger_node = trigger_node->next_sibling("trigger")) {
            trigger triggery;
            if (trigger_node->first_node("type")) {
                triggery.type = trigger_node->first_node("type")->value();
            }
            if (trigger_node->first_node("command")) {
                triggery.command = trigger_node->first_node("command")->value();
            }
            for (xml_node<> * action_node = trigger_node->first_node("action"); action_node; action_node = action_node->next_sibling("action")) {
                triggery.action.push_back(action_node->value());
            }
            if (trigger_node->first_node("print")) {
                triggery.print = trigger_node->first_node("print")->value();
            }
            if (trigger_node->first_node("condition")) {
                if (trigger_node->first_node("condition")->first_node("object")) {
                    triggery.conditioner.object = trigger_node->first_node("condition")->first_node("object")->value();
                }
                if (trigger_node->first_node("condition")->first_node("owner")) {
                    triggery.conditioner.owner = trigger_node->first_node("condition")->first_node("owner")->value();
                }
                if (trigger_node->first_node("condition")->first_node("has")) {
                    triggery.conditioner.has = trigger_node->first_node("condition")->first_node("has")->value();
                }
                if (trigger_node->first_node("condition")->first_node("status")) {
                    triggery.conditioner.status = trigger_node->first_node("condition")->first_node("status")->value();
                }
            }
            creaturey.triggers = triggery;
        }
        creature_vector.push_back(creaturey);
}

    int size_container = container_vector.size();
    int a = 0;

    int size_item = item_vector.size();
    int j = 0;

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
    int rv;

    while (1) {
        for (i = 0; i < size_room; i++) {
            if (string(curr_room.name) == room_vector[i].name) {
                rv = i;
                //cout << "rv " << i << endl;
            }
        }
        //cout << room_vector[rv].item_vector[0] << endl;
        prev_room = curr_room;
        check_exit = prev_room.getType(prev_room);
        cout << ">";
        //input command
        std::getline(std::cin, input_command);
        //spilt string
        string delimiter = " ";
        string command = input_command.substr(0, input_command.find(delimiter));
        //open exit
        if (string(input_command) == "open exit" && check_exit != "") {
            cout << "Game Over" << endl;
            return 0;
        } else if (string(input_command) == "i") {
            int l = 0;
            int size_inventory = inventory_vector.size();
            if (size_inventory == 0) {
                cout << "Inventory empty" << endl;
            } else {
                cout << "Inventory: ";
                for (l = 0; l < size_inventory; l++) {
                    if (l == 0) {
                        cout << inventory_vector[l];
                    } else {
                        cout << ", " << inventory_vector[l];
                    }

                }
                cout << endl;
            }
        } else if (command == "attack") {
            std::size_t pos = input_command.find("attack");
            std::string attack_command = input_command.substr(pos).substr(7);
            std::string delimiter = " ";
            //creature to be attacked
            string creature_only = attack_command.substr(0, attack_command.find(delimiter)); // creature
            std::size_t pos2 = attack_command.find("with");
            if (int(pos2) < attack_command.size()) {
                //item to attack creature with
                std::string attack_command2 = attack_command.substr(pos2).substr(5); //item
                //check if creature exists in room
                int size_room_creature = room_vector[rv].creature.size();
                int g;
                int creature_exists = 0;
                for (g = 0; g < size_room_creature; g++) {
                    if (string(room_vector[rv].creature[g]) == creature_only) {
                        //cout << room_vector[rv].creature[g] << endl;
                        creature_exists = 1;
                    }
                }
                //check if item exists in inventory
                int size_i = inventory_vector.size();
                int item_in_inventory = 0;
                int vector_num;
                for (g = 0; g < size_i; g++) {
                    if (inventory_vector[g] == attack_command2) {
                        //cout << inventory_vector[g] << endl;
                        item_in_inventory = 1;
                        vector_num = g;
                    }
                }
                int size_c = creature_vector.size();
                //cout << size_c << endl;
                int x;
                for (g = 0; g < size_c; g++) {
                    if (creature_vector[g].name == creature_only) {
                        int size_v = creature_vector[g].vulnerability.size();
                        //cout << size_v << "v" << endl;
                        for (x = 0; x < size_v; x++) {
                            if (attack_command2 == creature_vector[g].vulnerability[x]) {
                                cout << creature_vector[g].attack << endl;
                                int size_a = creature_vector[g].action.size();
                                //cout << size_a << "a" << endl;
                                for (int y = 0; y < size_a; y++) {
                                    input_command = creature_vector[g].action[y];
                                    string delimiter = " ";
                                    string command = input_command.substr(0, input_command.find(delimiter));
                                    if (string(input_command) == "open exit" && check_exit != "") {
                                        cout << "Game Over" << endl;
                                        return 0;
                                    } else if (string(input_command) == "i") {
                                        int l = 0;
                                        int size_inventory = inventory_vector.size();
                                        if (size_inventory == 0) {
                                            cout << "Inventory empty" << endl;
                                        } else {
                                            cout << "Inventory: ";
                                            for (l = 0; l < size_inventory; l++) {
                                                if (l == 0) {
                                                    cout << inventory_vector[l];
                                                } else {
                                                    cout << ", " << inventory_vector[l];
                                                }

                                            }
                                            cout << endl;
                                        }
                                    } else if (command == "turn" || command == "Turn") {
                                        std::size_t pos = input_command.find("on");
                                        std::string action_item = input_command.substr(pos);
                                        int length = action_item.size();
                                        string item_name = action_item.substr(3);
                                        //check if exists in inventory
                                        int k;
                                        int size_i = inventory_vector.size();
                                        int item_in_inventory = 0;
                                        int vector_num;
                                        for (k = 0; k < size_i; k++) {
                                            if (inventory_vector[k] == item_name) {
                                                item_in_inventory = 1;
                                                vector_num = k;
                                            }
                                        }
                                        if (item_in_inventory == 1) {
                                            int size_item_vector = item_vector.size();
                                            int m;
                                            for (m = 0; m < size_item_vector; m++) {
                                                if (item_vector[m].name == item_name) {
                                                    item_vector[m].turn_on_func(item_vector[m]);
                                                }
                                            }
                                        }
                                    } else if (command == "put" || command == "Put") {
                                        string delim = " ";
                                        string item_name = input_command.substr(4);
                                        size_t location_t = item_name.find("in");
                                        string location = item_name.substr(location_t + 3);
                                        item_name = item_name.substr(0, item_name.find(delim));
                                        int fbs = container_vector.size();
                                        int fbs2 = item_vector.size();
                                        int fbs3 = inventory_vector.size();
                                        int bsFlag = 0;
                                        for (i = 0; i < fbs; i++) {
                                            if (container_vector[i].name == location) {
                                                for (int j = 0; j < container_vector[i].accept.size(); j++)
                                                    if (container_vector[i].accept[j] == item_name) {
                                                        container_vector[i].item = item_name;
                                                        bsFlag = 1;
                                                    }
                                            }
                                            if (container_vector[i].accept.size() == 0) {
                                                bsFlag = 1;
                                                container_vector[i].item = item_name;
                                            }
                                        }
                                        if (bsFlag == 1) {
                                            for (i = 0; i < fbs3; i++) {
                                                if (inventory_vector[i] == item_name) {
                                                    inventory_vector.erase(inventory_vector.begin() + i);
                                                }
                                            }
                                        }
                                        for (int i = 0; i < fbs2; i++) {
                                            if (item_name == item_vector[i].name && bsFlag == 1) {
                                                item_vector[i].owner = location;
                                                cout << "You put the " << item_name << " in the " << location << endl;
                                            }
                                        }

                                    } else if (command == "open" || command == "Open") {
                                        string container_name = input_command.substr(5);
                                        int t;
                                        int size_rv = room_vector[rv].container_vector.size();
                                        int shtHead;
                                        for (t = 0; t < size_rv; t++) {
                                            if (room_vector[rv].container_vector[t] == container_name) {
                                                int size_c = container_vector.size();
                                                for (t = 0; t < size_c; t++) {
                                                    if (container_vector[t].name == container_name) {
                                                        shtHead = t;
                                                        break;
                                                    }
                                                }
                                                string itemx = container_vector[shtHead].item;
                                                if (itemx == "") {
                                                    cout << "Container cannot be opened" << endl;
                                                } else {
                                                    cout << container_name << " contains " << itemx << endl;
                                                    container_vector[shtHead].item = "";
                                                    room_vector[rv].item_vector.push_back(itemx);
                                                }
                                                break;
                                            }
                                        }
                                    } else if (command == "drop" || command == "Drop") {
                                        string item_name = input_command.substr(5);
                                        //check if item is in inventory
                                        int k;
                                        int size_i = inventory_vector.size();
                                        int item_exists = 0;
                                        int vector_num;
                                        for (k = 0; k < size_i; k++) {
                                            if (inventory_vector[k] == item_name) {
                                                item_exists = 1;
                                                vector_num = k;
                                            }
                                        }
                                        //add back to the room
                                        int fbs2 = item_vector.size();
                                        for (i = 0; i < fbs2; i++) {
                                            if (item_vector[i].name == item_name) {
                                                item_vector[i].owner = room_vector[rv].name;
                                            }
                                        }
                                        room_vector[rv].item_vector.push_back(inventory_vector[vector_num]);
                                        //remove item from vector
                                        inventory_vector.erase(inventory_vector.begin() + vector_num);
                                    } else if (command == "delete" || command == "Delete") {
                                        string delim = " ";
                                        string item_name = input_command.substr(7);
                                        string location;
                                        int fbs = item_vector.size();
                                        for (i = 0; i < fbs; i++) {
                                            if (item_vector[i].name == item_name) {
                                                location = item_vector[i].owner;
                                                item_vector[i].owner = "";
                                            }
                                        }
                                        if (location == "inventory") {
                                            int fbs2 = inventory_vector.size();
                                            for (i = 0; i < fbs2; i++) {
                                                if (inventory_vector[i] == item_name) {
                                                    inventory_vector.erase(inventory_vector.begin() + i);
                                                }
                                            }
                                        } else {
                                            int fbs2 = room_vector.size();
                                            int fbs3;
                                            for (i = 0; i < fbs2; i++) {
                                                if (room_vector[i].name == location) {
                                                    fbs3 = room_vector[i].item_vector.size();
                                                    for (int j = 0; j < fbs3; j++) {
                                                        room_vector[i].item_vector.erase(room_vector[i].item_vector.begin() + j);
                                                    }
                                                }
                                            }
                                        }
                                    } else if (command == "add" || command == "Add") {
                                        string delim = " ";
                                        string item_name = input_command.substr(4);
                                        size_t location_t = item_name.find("to");
                                        string location = item_name.substr(location_t + 3);
                                        item_name = item_name.substr(0, item_name.find(delim));
                                        int fbs = room_vector.size();
                                        int fbs2 = item_vector.size();
                                        int fbs3 = creature_vector.size();
                                        int bsFlag = 0;
                                        for (int i = 0; i < fbs2; i++) {
                                            if (item_name == item_vector[i].name) {
                                                item_vector[i].owner = location;
                                                bsFlag = 1;
                                            }
                                        }
                                        //cout << item_name << endl;
                                        for (i = 0; i < fbs; i++) {
                                            if (room_vector[i].name == location) {
                                                //cout << location << endl;
                                                if (bsFlag == 1) {
                                                    room_vector[i].item_vector.push_back(item_name);
                                                } else {
                                                    room_vector[i].creature.push_back(item_name);
                                                }
                                                //cout << room_vector[i].item_vector[0] << endl;
                                            }
                                        }
                                        for (i = 0; i < fbs3; i++) {
                                            if (creature_vector[i].name == item_name) {
                                                creature_vector[i].owner = location;
                                            }
                                        }
                                    } else if (command == "update" || command == "Update") {
                                        string delim = " ";
                                        string object = input_command.substr(7);
                                        size_t msg_t = object.find("to");
                                        string msg = object.substr(msg_t + 3);
                                        object = object.substr(0, object.find(delim));
                                        int iflag = 0;
                                        int test_i, test_c;
                                        int size_i = item_vector.size();
                                        int size_c = container_vector.size();
                                        int i;
                                        for (i = 0; i < size_i; i++) {
                                            if (item_vector[i].name == object) {
                                                item_vector[i].status = msg;
                                                iflag = 1;
                                                test_i = i;
                                                break;
                                            }
                                        }
                                        if (iflag == 0) {
                                            for (i = 0; i < size_c; i++) {
                                                if (container_vector[i].name == object) {
                                                    container_vector[i].status = msg;
                                                    test_c = i;
                                                    break;
                                                }
                                            }
                                        }



                                    } else if (command == "game" || command == "Game") {
                                        //size_t msg_t = input_command.find("over");
                                        string msg = input_command.substr(5);
                                        //cout << msg << endl;
                                        if (msg == "over" || msg == "Over") {
                                            cout << "Victory!" << endl;
                                            return 0;
                                        }
                                    } else if (command == "take" || command == "Take") { //take item and adds to inventory
                                        string item_name = input_command.substr(5);
                                        //check if item exists in inventory
                                        int k;
                                        int size_i = inventory_vector.size();
                                        int item_exists = 0;
                                        int item_num;
                                        for (k = 0; k < size_i; k++) {
                                            if (inventory_vector[k] == item_name) {
                                                cout << "Item exists in inventory" << endl;
                                                int item_num = k;
                                                item_exists = 1;
                                            }
                                        }
                                        if (room_vector[rv].getItem(room_vector[rv], item_name) && item_exists == 0) {
                                            //add to inventory   
                                            inventory_vector.push_back(item_name);
                                            cout << "Item " << item_name << " added to inventory" << endl;
                                            //remove item from current room
                                            int b;
                                            int c;
                                            int item_remove_room;
                                            int fbs2 = item_vector.size();
                                            for (i = 0; i < fbs2; i++) {
                                                if (item_vector[i].name == item_name) {
                                                    item_vector[i].owner = "inventory";
                                                }
                                            }
                                            for (b = 0, c = 0; b < room_vector[rv].item_vector.size(); b++, c++) {
                                                if (item_name == room_vector[rv].item_vector[c]) {
                                                    item_remove_room = c;
                                                    room_vector[rv].item_vector.erase(room_vector[rv].item_vector.begin() + c);
                                                }
                                            }
                                        }//item that doesn't exist
                                        else if (!room_vector[rv].getItem(room_vector[rv], item_name) && item_exists == 0) {
                                            cout << "Command not recognized" << endl;
                                        }
                                    } else if (string(input_command) == "n" || "s" || "e" || "w") {
                                        curr_room_str = prev_room.moveRoom(prev_room, input_command);
                                        if (string(curr_room_str) == "error") {
                                            cout << "Command not recognized" << endl;
                                        } else if (prev_room.getName(prev_room) != curr_room_str) {
                                            for (i = 0; i < size_room; i++) {
                                                if (string(room_vector[i].getName(room_vector[i])) == curr_room_str) {
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
                                break;
                            }
                        }
                        break;
                    }
                }
            } else {
                cout << "command not recognized" << endl;
            }
        } else if (command == "turn") {
            std::size_t pos = input_command.find("on");
            if (int(pos) < input_command.size()) {
                std::string action_item = input_command.substr(pos);
                int length = action_item.size();
                string item_name = action_item.substr(3);
                //check if exists in inventory
                int k;
                int size_i = inventory_vector.size();
                int item_in_inventory = 0;
                int vector_num;
                for (k = 0; k < size_i; k++) {
                    if (inventory_vector[k] == item_name) {
                        item_in_inventory = 1;
                        vector_num = k;
                    }
                }
                if (item_in_inventory == 1) {
                    int size_item_vector = item_vector.size();
                    int m;
                    for (m = 0; m < size_item_vector; m++) {
                        if (item_vector[m].name == item_name) {
                            item_vector[m].turn_on_func(item_vector[m]);
                            input_command = item_vector[m].action_on;
                            string delimiter = " ";
                            string command = input_command.substr(0, input_command.find(delimiter));
                            if (string(input_command) == "open exit" && check_exit != "") {
                                cout << "Game Over" << endl;
                                return 0;
                            } else if (string(input_command) == "i") {
                                int l = 0;
                                int size_inventory = inventory_vector.size();
                                if (size_inventory == 0) {
                                    cout << "Inventory empty" << endl;
                                } else {
                                    cout << "Inventory: ";
                                    for (l = 0; l < size_inventory; l++) {
                                        if (l == 0) {
                                            cout << inventory_vector[l];
                                        } else {
                                            cout << ", " << inventory_vector[l];
                                        }

                                    }
                                    cout << endl;
                                }
                            } else if (command == "turn") {
                                std::size_t pos = input_command.find("on");
                                std::string action_item = input_command.substr(pos);
                                int length = action_item.size();
                                string item_name = action_item.substr(3);
                                //check if exists in inventory
                                int k;
                                int size_i = inventory_vector.size();
                                int item_in_inventory = 0;
                                int vector_num;
                                for (k = 0; k < size_i; k++) {
                                    if (inventory_vector[k] == item_name) {
                                        item_in_inventory = 1;
                                        vector_num = k;
                                    }
                                }
                                if (item_in_inventory == 1) {
                                    int size_item_vector = item_vector.size();
                                    int m;
                                    for (m = 0; m < size_item_vector; m++) {
                                        if (item_vector[m].name == item_name) {
                                            item_vector[m].turn_on_func(item_vector[m]);
                                        }
                                    }
                                }
                            } else if (command == "put") {
                                string delim = " ";
                                string item_name = input_command.substr(4);
                                size_t location_t = item_name.find("in");
                                string location = item_name.substr(location_t + 3);
                                item_name = item_name.substr(0, item_name.find(delim));
                                int fbs = container_vector.size();
                                int fbs2 = item_vector.size();
                                int fbs3 = inventory_vector.size();
                                int bsFlag = 0;
                                for (i = 0; i < fbs; i++) {
                                    if (container_vector[i].name == location) {
                                        for (int j = 0; j < container_vector[i].accept.size(); j++)
                                            if (container_vector[i].accept[j] == item_name) {
                                                container_vector[i].item = item_name;
                                                bsFlag = 1;
                                            }
                                    }
                                    if (container_vector[i].accept.size() == 0) {
                                        bsFlag = 1;
                                        container_vector[i].item = item_name;
                                    }
                                }
                                if (bsFlag == 1) {
                                    for (i = 0; i < fbs3; i++) {
                                        if (inventory_vector[i] == item_name) {
                                            inventory_vector.erase(inventory_vector.begin() + i);
                                        }
                                    }
                                }
                                for (int i = 0; i < fbs2; i++) {
                                    if (item_name == item_vector[i].name && bsFlag == 1) {
                                        item_vector[i].owner = location;
                                        cout << "You put the " << item_name << " in the " << location << endl;
                                    }
                                }

                            } else if (command == "open") {
                                string container_name = input_command.substr(5);
                                int t;
                                int size_rv = room_vector[rv].container_vector.size();
                                int shtHead;
                                for (t = 0; t < size_rv; t++) {
                                    if (room_vector[rv].container_vector[t] == container_name) {
                                        int size_c = container_vector.size();
                                        for (t = 0; t < size_c; t++) {
                                            if (container_vector[t].name == container_name) {
                                                shtHead = t;
                                                break;
                                            }
                                        }
                                        string itemx = container_vector[shtHead].item;
                                        if (itemx == "") {
                                            cout << "Container cannot be opened" << endl;
                                        } else {
                                            cout << container_name << " contains " << itemx << endl;
                                            container_vector[shtHead].item = "";
                                            room_vector[rv].item_vector.push_back(itemx);
                                        }
                                        break;
                                    }
                                }
                            } else if (command == "drop") {
                                string item_name = input_command.substr(5);
                                //check if item is in inventory
                                int k;
                                int size_i = inventory_vector.size();
                                int item_exists = 0;
                                int vector_num;
                                for (k = 0; k < size_i; k++) {
                                    if (inventory_vector[k] == item_name) {
                                        item_exists = 1;
                                        vector_num = k;
                                    }
                                }
                                //add back to the room
                                int fbs2 = item_vector.size();
                                for (i = 0; i < fbs2; i++) {
                                    if (item_vector[i].name == item_name) {
                                        item_vector[i].owner = room_vector[rv].name;
                                    }
                                }
                                room_vector[rv].item_vector.push_back(inventory_vector[vector_num]);
                                //remove item from vector
                                inventory_vector.erase(inventory_vector.begin() + vector_num);
                            } else if (command == "delete") {
                                string delim = " ";
                                string item_name = input_command.substr(7);
                                string location;
                                int fbs = item_vector.size();
                                for (i = 0; i < fbs; i++) {
                                    if (item_vector[i].name == item_name) {
                                        location = item_vector[i].owner;
                                        item_vector[i].owner = "";
                                    }
                                }
                                if (location == "inventory") {
                                    int fbs2 = inventory_vector.size();
                                    for (i = 0; i < fbs2; i++) {
                                        if (inventory_vector[i] == item_name) {
                                            inventory_vector.erase(inventory_vector.begin() + i);
                                        }
                                    }
                                } else {
                                    int fbs2 = room_vector.size();
                                    int fbs3;
                                    for (i = 0; i < fbs2; i++) {
                                        if (room_vector[i].name == location) {
                                            fbs3 = room_vector[i].item_vector.size();
                                            for (int j = 0; j < fbs3; j++) {
                                                room_vector[i].item_vector.erase(room_vector[i].item_vector.begin() + j);
                                            }
                                        }
                                    }
                                }
                            } else if (command == "add") {
                                string delim = " ";
                                string item_name = input_command.substr(4);
                                size_t location_t = item_name.find("to");
                                string location = item_name.substr(location_t + 3);
                                item_name = item_name.substr(0, item_name.find(delim));
                                int fbs = room_vector.size();
                                int fbs2 = item_vector.size();
                                int fbs3 = creature_vector.size();
                                int bsFlag = 0;
                                for (int i = 0; i < fbs2; i++) {
                                    if (item_name == item_vector[i].name) {
                                        item_vector[i].owner = location;
                                        bsFlag = 1;
                                    }
                                }
                                //cout << item_name << endl;
                                for (i = 0; i < fbs; i++) {
                                    if (room_vector[i].name == location) {
                                        //cout << location << endl;
                                        if (bsFlag == 1) {
                                            room_vector[i].item_vector.push_back(item_name);
                                        } else {
                                            room_vector[i].creature.push_back(item_name);
                                        }
                                        //cout << room_vector[i].item_vector[0] << endl;
                                    }
                                }
                                for (i = 0; i < fbs3; i++) {
                                    if (creature_vector[i].name == item_name) {
                                        creature_vector[i].owner = location;
                                    }
                                }
                            } else if (command == "update") {
                                string delim = " ";
                                string object = input_command.substr(7);
                                size_t msg_t = object.find("to");
                                string msg = object.substr(msg_t + 3);
                                object = object.substr(0, object.find(delim));
                                int iflag = 0;
                                int test_i, test_c;
                                int size_i = item_vector.size();
                                int size_c = container_vector.size();
                                int i;
                                for (i = 0; i < size_i; i++) {
                                    if (item_vector[i].name == object) {
                                        item_vector[i].status = msg;
                                        iflag = 1;
                                        test_i = i;
                                        break;
                                    }
                                }
                                if (iflag == 0) {
                                    for (i = 0; i < size_c; i++) {
                                        if (container_vector[i].name == object) {
                                            container_vector[i].status = msg;
                                            test_c = i;
                                            break;
                                        }
                                    }
                                }



                            } else if (command == "game") {
                                //size_t msg_t = input_command.find("over");
                                string msg = input_command.substr(5);
                                //cout << msg << endl;
                                if (msg == "over") {
                                    cout << "Victory!" << endl;
                                    return 0;
                                }
                            } else if (command == "take") { //take item and adds to inventory
                                string item_name = input_command.substr(5);
                                //check if item exists in inventory
                                int k;
                                int size_i = inventory_vector.size();
                                int item_exists = 0;
                                int item_num;
                                for (k = 0; k < size_i; k++) {
                                    if (inventory_vector[k] == item_name) {
                                        cout << "Item exists in inventory" << endl;
                                        int item_num = k;
                                        item_exists = 1;
                                    }
                                }
                                if (room_vector[rv].getItem(room_vector[rv], item_name) && item_exists == 0) {
                                    //add to inventory   
                                    inventory_vector.push_back(item_name);
                                    cout << "Item " << item_name << " added to inventory" << endl;
                                    //remove item from current room
                                    int b;
                                    int c;
                                    int item_remove_room;
                                    int fbs2 = item_vector.size();
                                    for (i = 0; i < fbs2; i++) {
                                        if (item_vector[i].name == item_name) {
                                            item_vector[i].owner = "inventory";
                                        }
                                    }
                                    for (b = 0, c = 0; b < room_vector[rv].item_vector.size(); b++, c++) {
                                        if (item_name == room_vector[rv].item_vector[c]) {
                                            item_remove_room = c;
                                            room_vector[rv].item_vector.erase(room_vector[rv].item_vector.begin() + c);
                                        }
                                    }
                                }//item that doesn't exist
                                else if (!room_vector[rv].getItem(room_vector[rv], item_name) && item_exists == 0) {
                                    cout << "Command not recognized" << endl;
                                }
                            } else if (string(input_command) == "n" || "s" || "e" || "w") {
                                curr_room_str = prev_room.moveRoom(prev_room, input_command);
                                if (string(curr_room_str) == "error") {
                                    cout << "Command not recognized" << endl;
                                } else if (prev_room.getName(prev_room) != curr_room_str) {
                                    for (i = 0; i < size_room; i++) {
                                        if (string(room_vector[i].getName(room_vector[i])) == curr_room_str) {
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
                    }
                }
            } else {
                cout << "command not recognized" << endl;
            }

        } else if (command == "put") {
            string delim = " ";
            string item_name = input_command.substr(4);
            size_t location_t = item_name.find("in");
            if (int(location_t) < item_name.size()) {
                string location = item_name.substr(location_t + 3);
                item_name = item_name.substr(0, item_name.find(delim));
                int fbs = container_vector.size();
                int fbs2 = item_vector.size();
                int fbs3 = inventory_vector.size();
                int bsFlag = 0;
                for (i = 0; i < fbs; i++) {
                    if (container_vector[i].name == location) {
                        for (int j = 0; j < container_vector[i].accept.size(); j++)
                            if (container_vector[i].accept[j] == item_name) {
                                container_vector[i].item = item_name;
                                bsFlag = 1;
                                break;
                            }
                    }
                    if (container_vector[i].accept.size() == 0) {
                        bsFlag = 1;
                        container_vector[i].item = item_name;
                    }
                }
                if (bsFlag == 1) {
                    for (i = 0; i < fbs3; i++) {
                        if (inventory_vector[i] == item_name) {
                            inventory_vector.erase(inventory_vector.begin() + i);
                        }
                    }
                }
                for (int i = 0; i < fbs2; i++) {
                    if (item_name == item_vector[i].name && bsFlag == 1) {
                        item_vector[i].owner = location;
                        cout << "You put the " << item_name << " in the " << location << endl;
                        break;
                    }
                }
            } else {
                cout << "command not recognized" << endl;
            }

            //cout << item_name << endl;
        } else if (command == "open") {
            string container_name = input_command.substr(5);
            int t;
            int size_rv = room_vector[rv].container_vector.size();
            int shtHead;
            int flag = 0;
            for (t = 0; t < size_rv; t++) {
                if (room_vector[rv].container_vector[t] == container_name) {
                    int size_c = container_vector.size();
                    for (t = 0; t < size_c; t++) {
                        if (container_vector[t].name == container_name) {
                            shtHead = t;
                            break;
                        }
                    }
                    string itemx = container_vector[shtHead].item;
                    if (itemx == "") {
                        cout << "Container cannot be opened" << endl;
                    } else {
                        cout << container_name << " contains " << itemx << endl;
                        container_vector[shtHead].item = "";
                        room_vector[rv].item_vector.push_back(itemx);
                        flag = 1;
                    }
                    break;
                }
            }
            if (flag == 0) {
                cout << "This container doesn't exist" << endl;
            }
        } else if (command == "drop") {
            string item_name = input_command.substr(5);
            //check if item is in inventory
            int k;
            int size_i = inventory_vector.size();
            int item_exists = 0;
            int vector_num;
            for (k = 0; k < size_i; k++) {
                if (inventory_vector[k] == item_name) {
                    item_exists = 1;
                    vector_num = k;
                }
            }
            //add back to the room
            int fbs2 = item_vector.size();
            for (i = 0; i < fbs2; i++) {
                if (item_vector[i].name == item_name) {
                    item_vector[i].owner = room_vector[rv].name;
                }
            }
            if (item_exists == 1) {
                room_vector[rv].item_vector.push_back(inventory_vector[vector_num]);
                //remove item from vector
                inventory_vector.erase(inventory_vector.begin() + vector_num);
            }
            else{
                cout << "command not recognized" << endl;
            }
        } else if (command == "take") { //take item and adds to inventory
            string item_name = input_command.substr(5);
            //check if item exists in inventory
            int k;
            int size_i = inventory_vector.size();
            int item_exists = 0;
            int item_num;
            for (k = 0; k < size_i; k++) {
                if (inventory_vector[k] == item_name) {
                    cout << "Item exists in inventory" << endl;
                    int item_num = k;
                    item_exists = 1;
                }
            }
            if (room_vector[rv].getItem(room_vector[rv], item_name) && item_exists == 0) {
                //add to inventory   
                inventory_vector.push_back(item_name);
                cout << "Item " << item_name << " added to inventory" << endl;
                //remove item from current room
                int b;
                int c;
                int item_remove_room;
                int fbs2 = item_vector.size();
                for (i = 0; i < fbs2; i++) {
                    if (item_vector[i].name == item_name) {
                        item_vector[i].owner = "inventory";
                    }
                }
                for (b = 0, c = 0; b < room_vector[rv].item_vector.size(); b++, c++) {
                    if (item_name == room_vector[rv].item_vector[c]) {
                        item_remove_room = c;
                        room_vector[rv].item_vector.erase(room_vector[rv].item_vector.begin() + c);
                    }
                }
            }//item that doesn't exist
            else if (!room_vector[rv].getItem(room_vector[rv], item_name) && item_exists == 0) {
                cout << "Command not recognized" << endl;
            }
        } else if (string(input_command) == "n" || "s" || "e" || "w") {
            curr_room_str = prev_room.moveRoom(prev_room, input_command);
            if (string(curr_room_str) == "error") {
                cout << "Command not recognized" << endl;
            } else if (prev_room.getName(prev_room) != curr_room_str) {
                for (i = 0; i < size_room; i++) {
                    if (string(room_vector[i].getName(room_vector[i])) == curr_room_str) {
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

    //return 0;
}


/*

## 강의

## blogs and websites

*/

#include <iostream>
#include <fstream>
#include <iomanip>
// #include <stdlib.h>
#include <sstream>
#include <vector>
#include <ctype.h>

using namespace std;

vector<string> nodeGetter(string input, char delimter);
void check_eligibility(vector<string> nodes);
vector<string> mapGetter(string input, char delimiter);
void print_map(vector<vector<string> > map, vector<string> nodes);
void adjacency_list(vector<vector<string> > map, vector<string> nodes);
bool check_data(string data);

int main(){
    // open data file of the adjacency matrix of the map
    ifstream myfile("hw6_data.txt");
    if(myfile.is_open()){}
    else{
        cout << "[ERROR] failed opening file." << endl;
        cout << "Terminating program." << endl;
        return 0x0;
    }

    // retreive informations about the existing nodes in the map
    string line;
    getline(myfile, line);
    vector<string> nodes = nodeGetter(line, '\t');

    // check whether the number of nodes are eligible to continue the program.
    check_eligibility(nodes);
    
    // get map data information for each nodes
    vector<vector<string> > map;
    int count = 0;
    while(getline(myfile, line)){
        map.push_back(mapGetter(line, '\t'));
        count++;
    }

    // print adjacency matrix of map
    cout << "Adjancy Matrix of map." << endl;
    print_map(map, nodes);

    // prints adjacency list of map
    cout << "Adjancy List of map." << endl;
    adjacency_list(map, nodes);

    myfile.close();

    return 0x0;
}

// retreive informations about the existing nodes in the map
vector<string> nodeGetter(string input, char delimter){
    vector<string> nodes;
    stringstream ss(input);
    string temp;

    while(ss >> temp){
        nodes.push_back(temp);
    }
    return nodes;
}

// check whether the number of nodes are eligible to continue the program.
void check_eligibility(vector<string> nodes){
    cout << "The number of nodes : " << nodes.size() << endl;
    if(nodes.size() > 30){
        cout << "The number of nodes should be less than or equall to 30." << endl;
        cout << "Terminating program." << endl;
        exit(0);
    }else{
        cout << "Eligible size to continue with program." << endl;
    }cout << endl;
}

// get map data information for each nodes
vector<string> mapGetter(string input, char delimiter){
    vector<string> map;
    stringstream ss(input);
    string temp;

    ss >> temp;

    while(ss >> temp){
        map.push_back(temp);
    }

    return map;
}

// print adjacency matrix of map
void print_map(vector<vector<string> > map, vector<string> nodes){
    int a = 11;
    cout << "           ";
    for(int i=0; i < nodes.size(); i++){
        cout << left << setw(a) << setfill(' ') << nodes[i];
    }cout << endl;

    for(int i=0; i < map.size(); i++){
        cout << left << setw(a) << setfill(' ') << nodes[i];
        for(int j=0; j < map[i].size(); j++){
            cout << left << setw(a) << setfill(' ') << map[i][j];
        }cout << endl;
    }cout << endl;
}

// prints adjacency list of map
void adjacency_list(vector<vector<string> > map, vector<string> nodes){
    for(int i=0; i < nodes.size(); i++){
        cout << nodes[i];
        for(int j=0; j < map[i].size(); j++){
            if(i != j){
                if(check_data(map[i][j])){
                    cout << " --> " << nodes[j];
                }
            }
        }cout << endl;
    }cout << endl;
}

// check whether the data is a leading path or not
bool check_data(string data){
    for(int i=0; i < data.size(); i++){
        if(!isdigit(data[i])) return false;
    }
    return true;
}
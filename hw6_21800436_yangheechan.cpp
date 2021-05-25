/*

## 강의
없음

## blogs and websites
https://www.geeksforgeeks.org/program-to-find-transpose-of-a-matrix/
https://www.tutorialspoint.com/Passing-two-dimensional-array-to-a-Cplusplus-function

*/

#include <iostream>
#include <fstream>
#include <iomanip>
// #include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;

vector<string> nodeGetter(string input, char delimter);
vector<string> mapGetter(string input, char delimiter);
void print_map(vector<vector<string> > map, vector<string> nodes);

int main(){
    // open data file of the adjacency matrix of the map
    ifstream myfile("hw6_data.txt");
    if(myfile.is_open()){}
    else{
        cout << "[ERROR] failed opening file." << endl;
        cout << "Terminating program." << endl;
        return 0x0;
    }

    // retreive informations about the xisting nodes in the map
    string line;
    getline(myfile, line);
    vector<string> nodes = nodeGetter(line, '\t');
    
    vector<vector<string> > map;
    int count = 0;
    while(getline(myfile, line)){
        map.push_back(mapGetter(line, '\t'));
        count++;
    }

    print_map(map, nodes);

    return 0x0;
}

vector<string> nodeGetter(string input, char delimter){
    vector<string> nodes;
    stringstream ss(input);
    string temp;

    while(ss >> temp){
        nodes.push_back(temp);
    }
    return nodes;
}

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
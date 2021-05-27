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
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

struct Node {
    int position;
    string init_d;
    int distance;
    int predecessor;
};

vector<string> nodeGetter(string input, char delimter);
void check_eligibility(vector<string> nodes);
vector<Node> mapGetter(string input, char delimiter);
void print_map(vector<vector<Node> > map, vector<string> nodes);
void adjacency_list(vector<vector<Node> > map, vector<string> nodes);
bool check_data(string data);
void init_single_source(vector<Node> &map);
Node make_node(string temp, int distance, int predecessor, int position);
void dijkstra(vector<vector<Node> > map, vector<string> nodes);
Node extract_min(vector<Node> &Q);
void update_map(vector<Node> &map, vector<string> nodes, Node U);

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
    vector<vector<Node> > map;
    int count = 0;
    while(getline(myfile, line)){
        map.push_back(mapGetter(line, '\t'));
        count++;
    }

    // print adjacency matrix of map
    cout << "Adjancy Matrix of original map." << endl;
    print_map(map, nodes);

    // prints adjacency list of map
    cout << "Adjancy List of original map." << endl;
    adjacency_list(map, nodes);

    dijkstra(map, nodes);

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
vector<Node> mapGetter(string input, char delimiter){
    vector<Node> map;
    stringstream ss(input);
    string temp;

    ss >> temp;

    int position = 0;
    while(ss >> temp){
        map.push_back(make_node(temp, -1, -1, position));
        position++;
    }

    return map;
}

// print adjacency matrix of map
void print_map(vector<vector<Node> > map, vector<string> nodes){
    int a = 11;
    cout << "           ";
    for(int i=0; i < nodes.size(); i++){
        cout << left << setw(a) << setfill(' ') << nodes[i];
    }cout << endl;

    for(int i=0; i < map.size(); i++){
        cout << left << setw(a) << setfill(' ') << nodes[i];
        for(int j=0; j < map[i].size(); j++){
            cout << left << setw(a) << setfill(' ') << map[i][j].init_d;
        }cout << endl;
    }cout << endl;
}

// prints adjacency list of map
void adjacency_list(vector<vector<Node> > map, vector<string> nodes){
    for(int i=0; i < nodes.size(); i++){
        cout << nodes[i];
        for(int j=0; j < map[i].size(); j++){
            if(i != j){
                if(check_data(map[i][j].init_d)){
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

void init_single_source(vector<Node> &map){
    for(int i=0; i < map.size(); i++){
        map[i].distance = numeric_limits<int>::max();
        map[i].predecessor = -1;
    }
    map[0].distance = 0;
}

Node make_node(string temp, int distance, int predecessor, int position){
    Node init;

    init.position = position;
    init.init_d = temp;
    init.distance = distance;
    init.predecessor = predecessor;

    return init;
}

void dijkstra(vector<vector<Node> > dijkstra_map, vector<string> nodes){
    for(int i=0; i < dijkstra_map.size(); i++){
        init_single_source(dijkstra_map[i]);
        vector<Node> Q = dijkstra_map[i];
        while(!Q.empty()){
            Node U = extract_min(Q);
            dijkstra_map[i][U.position] = U;
            for(int j=0; j < dijkstra_map[U.position].size(); j++){
                
            }
        }
    }
}

Node extract_min(vector<Node> &Q){
    int min= numeric_limits<int>::max();
    int target = 0;
    
    for(int i=0 ; i < Q.size(); i++){
        if(Q[i].distance < min){
            target = i;
            min = Q[i].distance;
        }
    }

    swap(Q[target], Q.back());
    Node min_adj = Q.back();
    Q.pop_back();
    
    return min_adj;
}

void update_map(vector<Node> &map, vector<string> nodes, Node U){
    for(int i=0; i < map.size(); i++){
    }
}

void relaxation(){
}
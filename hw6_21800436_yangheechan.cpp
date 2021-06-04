/*
## 강의
(ppt slide) 9. Chapter 24 shortest paths 

## blogs and websites
passing vector : https://www.geeksforgeeks.org/passing-vector-function-cpp/
set max : https://stackoverflow.com/questions/8690567/setting-an-int-to-infinity-in-c
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <limits>
#include <time.h>

using namespace std;

struct Node {
    int position;
    string init_d;
    int distance;
    int predecessor;
};

vector<string> nodeGetter(string input);
void check_eligibility(vector<string> nodes);
vector<Node> mapGetter(string input, int predecessor);
void print_map(vector<vector<Node> > map, vector<string> nodes);
void adjacency_list(vector<vector<Node> > map, vector<string> nodes);
bool check_data(string data);
void init_single_source(vector<Node> &map, int source);
Node make_node(string temp, int distance, int predecessor, int position);
Node extract_min(vector<Node> &Q);
void relaxation(Node U, Node &V, Node W);
void print_shortest_path(vector<vector<Node> > map, vector<string> nodes);
void dijkstra(vector<vector<Node> > map, vector<string> nodes);
void floyd_warshall(vector<vector<Node> > map, vector<string> nodes);

int main(){
    // open data file of the adjacency matrix of the map
    ifstream myfile("hw6.data");
    if(myfile.is_open()){}
    else{
        cout << "[ERROR] failed opening file." << endl;
        cout << "Terminating program." << endl;
        return 0x0;
    }

    // retreive informations about the existing nodes in the map
    string line;
    getline(myfile, line);
    vector<string> nodes = nodeGetter(line);

    // check whether the number of nodes are eligible to continue the program.
    check_eligibility(nodes);
    
    // get map data information for each nodes
    vector<vector<Node> > map;
    int count = 0;
    while(getline(myfile, line)){
        map.push_back(mapGetter(line, count));
        count++;
    }

    // // print adjacency matrix of map
    // cout << "Adjancy Matrix of original map." << endl;
    // print_map(map, nodes);

    // // prints adjacency list of map
    // cout << "Adjancy List of original map." << endl;
    // adjacency_list(map, nodes);

    // applies dijkstra's algorithm to the map for each node as a source
    // to find the distance of shortest path from each node as source to other nodes
    dijkstra(map, nodes);

    // applies floyds-warshall's algorithm to the map for each node as a source
    // to find the distance of shortest path from each node as source to other nodes
    floyd_warshall(map, nodes);

    myfile.close();

    return 0x0;
}

// retreive informations about the existing nodes in the map
vector<string> nodeGetter(string input){
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
vector<Node> mapGetter(string input, int predecessor){
    vector<Node> map;
    stringstream ss(input);
    string temp;

    ss >> temp;

    int position = 0;
    while(ss >> temp){
        map.push_back(make_node(temp, 0x0, predecessor, position));
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

// initiate all the nodes with max value excluding the source node
void init_single_source(vector<Node> &map, int source){
    for(int i=0; i < map.size(); i++){
        map[i].distance = numeric_limits<int>::max();
        map[i].predecessor = -1;
    }
    map[source].distance = 0;
}

// creates a node to be added to the map
Node make_node(string temp, int distance, int predecessor, int position){
    Node init;

    init.position = position;
    init.init_d = temp;
    if(check_data(temp)){
        if(stoi(temp) == 0){
            init.predecessor = -1;
        }else{
            init.predecessor = predecessor;
        }
        init.distance = stoi(temp);
    }else{
        init.distance = numeric_limits<int>::max();;
        init.predecessor = -1;
    }

    return init;
}

// extracts node with the minimum distance from a map
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

// changes the distance of a node to a shorter path distance
void relaxation(Node U, Node &V, Node W){
    if(V.distance > U.distance + stoi(W.init_d)){
        V.distance = U.distance + stoi(W.init_d);
        V.predecessor = U.position;
    }
}

// prints the result map for the distance of the shortest path
// for each node as a source to other nodes
void print_shortest_path(vector<vector<Node> > map, vector<string> nodes){
    int a = 11;
    cout << "           ";
    for(int i=0; i < nodes.size(); i++){
        cout << left << setw(a) << setfill(' ') << nodes[i];
    }cout << endl;

    for(int i=0; i < map.size(); i++){
        cout << left << setw(a) << setfill(' ') << nodes[i];
        for(int j=0; j < map[i].size(); j++){
            cout << left << setw(a) << setfill(' ') << map[i][j].distance;
        }cout << endl;
    }cout << endl;
}

// applies dijkstra's algorithm to the map for each node as a source
// to find the distance of shortest path from each node as source to other nodes
void dijkstra(vector<vector<Node> > dijkstra_map, vector<string> nodes){
    clock_t t;
    t = clock();

    for(int i=0; i < dijkstra_map.size(); i++){
        init_single_source(dijkstra_map[i], i);
        vector<Node> Q = dijkstra_map[i];
        while(!Q.empty()){
            Node U = extract_min(Q);
            dijkstra_map[i][U.position] = U;
            for(int j=0; j < dijkstra_map[U.position].size(); j++){
                if(check_data(dijkstra_map[U.position][j].init_d)){
                    for(int k=0; k < Q.size(); k++){
                        if(Q[k].position == dijkstra_map[i][j].position){
                            relaxation(U, Q[k], dijkstra_map[U.position][j]);
                        }
                    }
                }
            }
        }
    }

    t = clock() - t;
    
    cout << "It took " << (double)t / CLOCKS_PER_SEC << " seconds to computer shortest path between cities with Dijkstra's algorithm as follows." << endl;
    print_shortest_path(dijkstra_map, nodes);
}

// applies floyds-warshall's algorithm to the map for each node as a source
// to find the distance of shortest path from each node as source to other nodes
void floyd_warshall(vector<vector<Node> > floyd_map, vector<string> nodes){
    clock_t t;
    t = clock();

    vector<vector<vector<Node> > > D;
    for(int i=0; i < floyd_map.size(); i++){
        D.push_back(floyd_map);
    }

    for(int k = 1; k < floyd_map.size(); k++){
        for(int i = 0; i < floyd_map.size(); i++){
            for(int j = 0; j < floyd_map.size(); j++){
                if(D[k-1][i][k].distance != numeric_limits<int>::max() && D[k-1][k][j].distance != numeric_limits<int>::max()){
                    if(D[k-1][i][k].distance + D[k-1][k][j].distance < D[k-1][i][j].distance){
                        D[k][i][j].distance = D[k-1][i][k].distance + D[k-1][k][j].distance;
                        D[k][i][j].predecessor = k;
                    }else{
                        D[k][i][j].distance = D[k-1][i][j].distance;
                        D[k][i][j].predecessor = D[k-1][i][j].predecessor;
                    }
                }else{
                    D[k][i][j].distance = D[k-1][i][j].distance;
                    D[k][i][j].predecessor = D[k-1][i][j].predecessor;
                }
            }
        }
    }

    t = clock() - t;
    
    cout << "It took " << (double)t / CLOCKS_PER_SEC << " seconds to computer shortest path between cities with Floyd algorithm as follows." << endl;
    print_shortest_path(D[floyd_map.size()-1], nodes);
}
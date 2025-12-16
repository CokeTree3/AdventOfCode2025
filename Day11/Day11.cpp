#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{

    string name;
    vector<string> stringList;
    vector<Node*> outputList;
    bool hasEnd = false;

    Node(string name){
        this->name = name;
    }

    const inline bool operator==(const Node& rhs){
        return this->name == rhs.name;
    }

    const inline bool operator==(const string& rhs){
        return this->name == rhs;
    }

    void setEnd(){
        hasEnd = true;
    }

    void addOutConnection(Node* output){
        outputList.push_back(output);
    }

    void printNode(){
        cout << name << ": ";
        for(auto out : outputList){
            cout << out->name << " ";
        }
        cout << endl;
    }
};

int traverse_graph_1(Node* startNode){
    int endReached = 0;

    if(startNode->hasEnd) return 1;

    for(Node* outNode : startNode->outputList){
        endReached = endReached + traverse_graph_1(outNode);
    }

    return endReached;
}

int traverse_graph_2(Node* startNode, unordered_set<Node*>& path){
    int endReached = 0;

    if(startNode->hasEnd){
        return 0;
    }
    if(startNode->name == "dac"){
        return 1;
    }

    path.insert(startNode);

    for(int i = 0; i < startNode->outputList.size(); i++){
        Node* outNode = startNode->outputList[i];

        endReached = endReached + traverse_graph_2(outNode, path);
    }
    path.erase(startNode);

    return endReached;
}

unsigned long part_1(vector<Node> deviceList){
    unsigned long sum = 0;

    Node* startNode;
    for(int i = 0; i < deviceList.size(); i++){
        if(deviceList[i] == "you"){
            startNode = &(deviceList[i]);
            break;
        }
    }

    sum = traverse_graph_1(startNode);

    return sum;
}

unsigned long part_2(vector<Node> deviceList){
    unsigned long sum = 0;

    Node* startNode;
    for(int i = 0; i < deviceList.size(); i++){
        if(deviceList[i] == "svr"){
            startNode = &(deviceList[i]);
            break;
        }
    }

    unordered_set<Node*> path;
    cout << "trav start " << startNode->name << endl;
    int badVisits = 0;
    sum = traverse_graph_2(startNode, path); 

    cout << "asdasdsd " << badVisits << endl;

    return sum;
}


int main(){

    ifstream f("input.txt");
    
    if(!f.is_open()){
        cout << "file read error" << endl;
        return 1;
    }

    string inpString;
    vector<Node> deviceList;
    unordered_map<string, vector<string>> lineList;

    while(getline(f, inpString)){
        
        string name = inpString.substr(0, inpString.find(":"));

        string outputsString = inpString.substr(inpString.find(":")+2);

        vector<string> outputList;
        string out;
        stringstream temp(outputsString);

        while(temp >> out){
            outputList.push_back(out);
            
        }
        lineList.insert({name, outputList});
    }

    for(auto line : lineList){
        Node device(line.first);

        deviceList.push_back(device);
    }

    for(auto line : lineList){
        for(int i = 0; i < deviceList.size(); i++){
            if(deviceList[i].name == line.first){
                
                for(string outName : line.second){

                    if(outName == "out"){
                        deviceList[i].setEnd();
                        break;
                    }

                    for(int j = 0; j < deviceList.size(); j++){
                        if(deviceList[j].name == outName){
                            deviceList[i].addOutConnection(&deviceList[j]);
                        }
                    }
                }
                break;
            }
        }
    }
    cout << endl;
    cout << "Answer to Part 1: " << part_1(deviceList) << endl;
    //cout << "Answer to Part 2: " << part_2(deviceList) << endl;


    return 0;
}

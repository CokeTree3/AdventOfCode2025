
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

struct Node{
    int x;
    int y;
    int z;

    Node* before = nullptr;
    Node* after = nullptr;

    bool end = false;
    bool mark = false;

    Node(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
        Node* endNode = new Node();
        endNode->end = true;
        this->after = endNode;
    }

    Node(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    int traverse_circuit(){

        int nodeCount = 1;

        Node* cur = this;

        while(cur->after->end != true){
            
            nodeCount++;
            //cout << "forw " << &cur << endl;
            cur = cur->after;

        }
        if(cur->after->mark) return 0;
        cur->after->mark = true;
        

        cur = this->before;

        while(cur != nullptr){
            nodeCount++;
            //cout << "backw" << endl;
            cur = cur->before;
        }

        return nodeCount;
    }

    bool equals(Node* p2){
        if(this->x == p2->x && this->y == p2->y && this->z == p2->z) return true;
        return false;
    }

    Node* get_first_node(){
        Node* first = this;
        while(first->before != nullptr){
            first = first->before;
        }

        return first;
    }

    Node* get_last_node(){
        Node* last = this;
        while(last->after->end != true){
            last = last->after;
        }

        return last;
    }

    void connect_node(Node* p2){
        /*if(this->after->end){
            
            Node* ss = p2.link_before(*this);
            this->after = &p2;
        }else{
            this->after->connect_node(p2);
        }*/
        cout << this << " " << this->get_last_node() << endl;
        Node* lastNode = this->get_last_node();
        lastNode->after = p2->get_first_node();

        p2->link_before(lastNode);

        cout << "asd" <<endl;
    }

    void link_before(Node* p2){

        cout << this << " " << this->get_first_node() << endl;
        this->get_first_node()->before = p2;
        
    }

    bool check_if_in_same_circuit(Node* p2){
        if(this->before == nullptr && this->after->end) return false;
        if(p2->before == nullptr && p2->after->end) return false;
        if(this->equals(p2)) return true;
        cout << "in" << this << "  " << this->before << endl;
        Node* cur = this->get_first_node();
        cout << "1st" << endl;
        while(cur->after->end != true){
            if(cur->equals(p2)) return true;
            cur = cur->after;
            cout << cur << endl;
        }
        return false;


        /*Node* circuitNode = this->before;
        while(circuitNode != nullptr){
            if(circuitNode->equals(p2)) return true;
            circuitNode = circuitNode->before;
        }

        circuitNode = this;
        while(circuitNode->end != true){
            if(circuitNode->equals(p2)) return true;
            circuitNode = circuitNode->after;
        }
        return false;*/
    }

    void print(){
        cout << "x=" << x << " y=" << y << " z=" << z << endl;
    }

};

unsigned long part_1(vector<Node> points){
    unsigned long sum = 1;
    cout << endl;
    int loopCount = 10;

    while(loopCount > 0){
        float shortestDist = FLT_MAX;
        Node* shortest1;
        Node* shortest2;

        loopCount--;

        for(int i = 0; i < points.size(); i++){
            
            Node* p1 = &points[i];

            for(int j = 0; j < points.size(); j++){
                if(i == j) continue;
                Node* p2 = &points[j];

                if(p1->check_if_in_same_circuit(p2)) continue;
                float distance = hypot(hypot(p1->x - p2->x, p1->y - p2->y), p1->z - p2->z);

                if(distance < shortestDist){
                    shortestDist = distance;
                    shortest1 = p1;
                    shortest2 = p2;
                }

            }
        }

        cout << loopCount << endl;

        shortest1->connect_node(shortest2);
        cout << "VVVV" << endl;
        cout << &shortest1 << " " << &shortest2 << endl;
        cout << shortest1->before << " " << shortest1->after << endl;
        cout << shortest2->before << " " << shortest2->after << endl;
        
    }
    vector<int> circuits;
    cout << "asdasd" << endl;

    for(int i = 0; i < points.size(); i++){
        int c = points[i].traverse_circuit();
        cout << c << endl;
        if( c > 0){
            //cout << c << endl;
            circuits.push_back(c);
        }
    }

    sort(circuits.begin(), circuits.end(), greater<int>());

    sum = circuits[0] * circuits[1] * circuits[3];

    cout << endl;
    return sum;
}

unsigned long part_2(){
    unsigned long sum = 0;
    
    return sum;
}

int main(){

    ifstream f("input.txt");
    
    if(!f.is_open()){
        cout << "file read error" << endl;
        return 1;
    }

    string inpString;
    vector<Node> points;

    while(getline(f, inpString)){
        char* temp = strtok(inpString.data(), ",");

        string c1;
        string c2;
        string c3;

        if(temp){
            c1 = string(temp);
            temp = strtok(nullptr, ",");
        }
        if(temp){
            c2 = string(temp);
            temp = strtok(nullptr, ",");
        }
        if(temp){
            c3 = string(temp);
            temp = strtok(nullptr, ",");
        }

        points.push_back(Node(stoi(c1), stoi(c2), stoi(c3)));
    }
    cout << "Answer to Part 1: " << part_1(points) << endl;
    cout << "Answer to Part 2: " << part_2() << endl;


    return 0;
}

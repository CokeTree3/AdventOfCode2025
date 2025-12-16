#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long part_1(vector<pair<long, long>> points){
    unsigned long sum = 0;
    unsigned long largestArea = 0;
    for(int i = 0; i < points.size(); i++){
        pair<long, long> p1 = points[i];
        for(int j = 0; j < points.size(); j++){
            pair<long, long> p2 = points[j];

            unsigned long area = (labs(p1.first - p2.first) + 1) * (labs(p1.second - p2.second) + 1);
            if(area > largestArea){
                largestArea = area;
            }
        }
    }

    cout << largestArea << endl;
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
    vector<pair<long, long>> points;

    while(getline(f, inpString)){
        if(inpString.find(',') != inpString.npos){
            string p1 = inpString.substr(0, inpString.find(","));
            string p2 = inpString.substr(inpString.find(",") + 1, inpString.npos);

            points.push_back(pair<long, long>(stol(p1), stol(p2)));
        }
    }
    cout << "Answer to Part 1: " << part_1(points) << endl;
    cout << "Answer to Part 2: " << part_2() << endl;


    return 0;
}
